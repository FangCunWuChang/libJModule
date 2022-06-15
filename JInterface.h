#pragma once
#include <JuceHeader.h>
#include "Arena.h"

//接口管理器，用于保存模块注册的接口

namespace jmadf {
	namespace inside {
		class CallBackObjectBase
		{
		public:
			CallBackObjectBase() = default;
			virtual ~CallBackObjectBase() = default;
		};

		//在修改CallBackObject的成员前请确保成员不会在堆上分配空间，否则将会造成内存泄漏！
		template<typename ...T>
		class CallBackObject final :
			public CallBackObjectBase
		{
			using F = std::function<void(const juce::String&, T...)>;
			F _data;
			const char* _typename;
			const F _empty = [](const juce::String&, T...) {};

		public:
			explicit CallBackObject(const F& data)
			{
				this->_data = data;
				this->_typename = typeid(F).name();
			};

			~CallBackObject() = default;

			const F& operator()()
			{
				if (strcmp(this->_typename, typeid(F).name())) {
					jassertfalse;//Interface args type isn't matched!
					return this->_empty;
				}
				return this->_data;
			};

			const char* type()
			{
				return this->_typename;
			};
		};

		//在修改CallBackObject的成员前请确保成员不会在堆上分配空间，否则将会造成内存泄漏！
		template<>
		class CallBackObject<void> final :
			public CallBackObjectBase
		{
			using F = std::function<void(const juce::String&)>;
			F _data;
			const char* _typename;
			const F _empty = [](const juce::String&) {};

		public:
			explicit CallBackObject(const F& data)
			{
				this->_data = data;
				this->_typename = typeid(F).name();
			};

			~CallBackObject() = default;

			const F& operator()()
			{
				if (strcmp(this->_typename, typeid(F).name())) {
					jassertfalse;//Interface args type isn't matched!
					return this->_empty;
				}
				return this->_data;
			};

			const char* type()
			{
				return this->_typename;
			};
		};
	}
	
	class JInterface final
	{
	public:
		JInterface() = default;
		~JInterface()
		{
			this->_lock.enterWrite();
			this->list.clear();
			this->_lock.exitWrite();
		};

	public:
		std::unique_ptr<leveldb::Arena> arena = std::make_unique<leveldb::Arena>();
		juce::HashMap<juce::String, inside::CallBackObjectBase*> list;
		juce::ReadWriteLock _lock;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JInterface)
	};
	
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
			instance->_lock.enterWrite();
			instance->list.set(
				key,
				new(instance->arena->Allocate(sizeof(U))) U(func)
			);
			instance->_lock.exitWrite();
		};

		static void call(JInterface* instance, const juce::String& caller, const juce::String& key, T ...args)
		{
			instance->_lock.enterRead();
			if (instance->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->list[key]);
				const F& func = (*obj)();
				func(caller, args...);
			}
			else {
				jassertfalse;//Interface isn't exists!
			}
			instance->_lock.exitRead();
		};
	};

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
			instance->_lock.enterWrite();
			instance->list.set(
				key,
				new(instance->arena->Allocate(sizeof(U))) U(func)
			);
			instance->_lock.exitWrite();
		};

		static void call(JInterface* instance, const juce::String& caller, const juce::String& key)
		{
			instance->_lock.enterRead();
			if (instance->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(instance->list[key]);
				const F& func = (*obj)();
				func(caller);
			}
			else {
				jassertfalse;//Interface isn't exists!
			}
			instance->_lock.exitRead();
		};
	};
}
