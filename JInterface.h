#pragma once
#include <JuceHeader.h>
#include "Arena.h"

//接口管理器，用于保存模块注册的接口

namespace jmadf {
	
	template<typename ...T>
	concept IsVoid = std::is_void_v<T...>;
	
	class JInterface final
	{
		class CallBackObjectBase
		{
		public :
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
					return [](const juce::String&, T...) {};
				}
				return this->_data;
			};
			
			operator const juce::String&()
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
					return [](const juce::String&) {};
				}
				return this->_data;
			};

			operator const juce::String& ()
			{
				return this->_typename;
			};
		};

	public:
		JInterface() = default;
		~JInterface()
		{
			this->_lock.enterWrite();
			this->list.clear();
			this->_lock.exitWrite();
		};

		template<typename ...T, class F = std::function<void(const juce::String&, T...)>, class U = JInterface::CallBackObject<T...>>
		void set(const juce::String& key, const F& func)
		{
			this->_lock.enterWrite();
			this->list.set(
				key,
				new(this->arena->Allocate(sizeof(U))) U(func)
			);
			this->_lock.exitWrite();
		};

		template<typename ...T, class F = std::function<void(const juce::String&, T...)>, class U = JInterface::CallBackObject<T...>>
		void call(const juce::String& caller, const juce::String& key, T ...args)
		{
			this->_lock.enterRead();
			if (this->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(this->list[key]);
				const F& func = (*obj)();
				func(caller, args...);
			}
			else {
				jassertfalse;//Interface isn't exists!
			}
			this->_lock.exitRead();
		};
		
		template<>
		void set<void>(const juce::String& key, const std::function<void(const juce::String&)>& func)
		{
			using F = std::function<void(const juce::String&)>;
			using U = JInterface::CallBackObject<void>;
			
			this->_lock.enterWrite();
			this->list.set(
				key,
				new(this->arena->Allocate(sizeof(U))) U(func)
			);
			this->_lock.exitWrite();
		};
		
		template<typename ...T>
		requires IsVoid<T...>
		void call(const juce::String& caller, const juce::String& key)
		{
			using F = std::function<void(const juce::String&)>;
			using U = JInterface::CallBackObject<void>;
			this->_lock.enterRead();
			if (this->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(this->list[key]);
				const F& func = (*obj)();
				func(caller);
			}
			else {
				jassertfalse;//Interface isn't exists!
			}
			this->_lock.exitRead();
		};
		
	private:
		std::unique_ptr<leveldb::Arena> arena = std::make_unique<leveldb::Arena>();
		juce::HashMap<juce::String, CallBackObjectBase*> list;
		juce::ReadWriteLock _lock;
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JInterface)
	};
}
