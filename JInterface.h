﻿#pragma once
#include <JuceHeader.h>

//接口管理器，用于保存模块注册的接口

namespace jmadf {
	namespace inside {
		template<typename ...T>
		static void emptyF(T...) {};//空函数

		static void emptyF_void() {};//void参数空函数

		class CallBackObjectBase
		{
		public:
			CallBackObjectBase() = default;
			virtual ~CallBackObjectBase() = 0;
			virtual const char* type() = 0;
		};//所有接口类的共同基类，便于脱离模板储存

		template<typename ...T>
		class CallBackObject final :
			public CallBackObjectBase
		{
			using F = std::function<void(const juce::String&, T...)>;
			const F _data;
			const char* _typename;

		public:
			explicit CallBackObject(const F& data)
				:_data(data), _typename(typeid(F).name())
			{};

			~CallBackObject() override = default;

			const F& get()
			{
				if (strcmp(this->_typename, typeid(F).name()) != 0) {
					jassertfalse;//Interface args type isn't matched!
					static F _empty = emptyF<const juce::String&, T...>;
					return _empty;
				}
				return this->_data;
			};

			const char* type() override
			{
				return this->_typename;
			};
		};//常态化接口类

		template<>
		class CallBackObject<void> final :
			public CallBackObjectBase
		{
			using F = std::function<void(const juce::String&)>;
			const F _data;
			const char* _typename;

		public:
			explicit CallBackObject(const F& data)
				:_data(data), _typename(typeid(F).name())
			{};

			~CallBackObject() override = default;

			const F& get()
			{
				if (strcmp(this->_typename, typeid(F).name()) != 0) {
					jassertfalse;//Interface args type isn't matched!
					static F _empty = emptyF<const juce::String&>;
					return _empty;
				}
				return this->_data;
			};

			const char* type() override
			{
				return this->_typename;
			};
		};//void类型特化接口类
	}
	
	class JInterface final
	{
	public:
		JInterface() = default;
		~JInterface()
		{
			juce::ScopedWriteLock locker(this->_lock);
			for (auto& i : this->_list) {
				delete i.second;
			}
			this->_list.clear();
		};

	public:
		std::map<juce::String, inside::CallBackObjectBase*> _list;
		juce::ReadWriteLock _lock;
	};//接口管理类
	
	template<typename ...T>
	class JInterfaceDao final
	{
		using F = std::function<void(const juce::String&, T...)>;
		using U = inside::CallBackObject<T...>;

		JInterfaceDao() = delete;
		~JInterfaceDao() = delete;

	public:
		static void set(JInterface* instance, const juce::String& key, const F& func)
		{
			juce::ScopedWriteLock locker(instance->_lock);
			instance->_list[key] = new U(func);
		};

		static const std::function<void(T...)> get(JInterface* instance, const juce::String& caller, const juce::String& key)
		{
			juce::ScopedReadLock locker(instance->_lock);
			if (instance->_list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->_list[key]);
				const F& func = obj->get();
				return [&caller, &func](T... args) {func(caller, std::forward<T>(args)...); };
			}
			else {
				jassertfalse;//Interface isn't exists!
				return inside::emptyF<T...>;
			}
		};
		static bool check(JInterface* instance, const juce::String& key)
		{
			juce::ScopedReadLock locker(instance->_lock);
			if (instance->_list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->_list[key]);
				using F = std::function<void(const juce::String&, T...)>;
				if (std::strcmp(obj->type(), typeid(F).name()) == 0) {
					return true;
				}
				jassertfalse;//类型不匹配
				return false;
			}
			jassertfalse;//未找到同名接口
			return false;
		};

		static void call(JInterface* instance, const juce::String& caller, const juce::String& key, T ...args)
		{
			JInterfaceDao<T...>::get(instance, caller, key)(std::forward<T>(args)...);
		};
	};//常态化接口数据访问对象

	template<>
	class JInterfaceDao<void> final
	{
		using F = std::function<void(const juce::String&)>;
		using U = inside::CallBackObject<void>;

		JInterfaceDao() = delete;
		~JInterfaceDao() = delete;

	public:
		static void set(JInterface* instance, const juce::String& key, const F& func)
		{
			juce::ScopedWriteLock locker(instance->_lock);
			instance->_list[key] = new U(func);
		};

		static const std::function<void(void)> get(JInterface* instance, const juce::String& caller, const juce::String& key)
		{
			juce::ScopedReadLock locker(instance->_lock);
			if (instance->_list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->_list[key]);
				const F& func = obj->get();
				return [&caller, &func] {func(caller); };
			}
			else {
				jassertfalse;//Interface isn't exists!
				return inside::emptyF_void;
			}
		};
		static bool check(JInterface* instance, const juce::String& key)
		{
			juce::ScopedReadLock locker(instance->_lock);
			if (instance->_list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->_list[key]);
				using F = std::function<void(const juce::String&)>;
				if (std::strcmp(obj->type(), typeid(F).name()) == 0) {
					return true;
				}
				jassertfalse;//类型不匹配
				return false;
			}
			jassertfalse;//未找到同名接口
			return false;
		};

		static void call(JInterface* instance, const juce::String& caller, const juce::String& key)
		{
			JInterfaceDao<void>::get(instance, caller, key)();
		};
	};//void类型特化数据访问对象
}
