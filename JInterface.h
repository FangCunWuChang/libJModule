#pragma once
#include <JuceHeader.h>

//接口管理器，用于保存模块注册的接口

namespace jmadf {
	namespace inside {
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
			const F _empty = [](const juce::String&, T...) {};

		public:
			explicit CallBackObject(const F& data)
				:_data(data), _typename(typeid(F).name())
			{};

			~CallBackObject() override = default;

			const F& operator()()
			{
				if (strcmp(this->_typename, typeid(F).name())) {
					jassertfalse;//Interface args type isn't matched!
					return this->_empty;
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
			const F _empty = [](const juce::String&) {};

		public:
			explicit CallBackObject(const F& data)
				:_data(data), _typename(typeid(F).name())
			{};

			~CallBackObject() override = default;

			const F& operator()()
			{
				if (strcmp(this->_typename, typeid(F).name())) {
					jassertfalse;//Interface args type isn't matched!
					return this->_empty;
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
			for (auto& i : this->list) {
				delete i.second;
			}
			this->list.clear();
		};

	public:
		std::map<juce::String, inside::CallBackObjectBase*> list;
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
			instance->list[key] = new U(func);
		};

		static void call(JInterface* instance, const juce::String& caller, const juce::String& key, T ...args)
		{
			juce::ScopedReadLock locker(instance->_lock);
			if (instance->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->list[key]);
				const F& func = (*obj)();
				func(caller, args...);
			}
			else {
				jassertfalse;//Interface isn't exists!
			}
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
			instance->list[key] = new U(func);
		};

		static void call(JInterface* instance, const juce::String& caller, const juce::String& key)
		{
			juce::ScopedReadLock locker(instance->_lock);
			if (instance->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->list[key]);
				const F& func = (*obj)();
				func(caller);
			}
			else {
				jassertfalse;//Interface isn't exists!
			}
		};
	};//void类型特化数据访问对象
}
