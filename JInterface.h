#pragma once
#include <JuceHeader.h>

//接口管理器，用于保存模块注册的接口

namespace jmadf {
	class JInterface final
	{
		class CallBackObjectBase
		{
			JUCE_LEAK_DETECTOR(CallBackObjectBase)
		};

		template<typename ...T>
		class CallBackObject final :
			private CallBackObjectBase
		{
			using F = std::function<void(const juce::String&, T...)>;
			F _data;
			const juce::String _typename;
		public:
			explicit CallBackObject(const F& data)
				:_data(data), _typename(typeid(F).name())
			{};

			const F& operator()()
			{
				if (this->_typename != typeid(F).name()) {
					jassertfalse;//Interface args type isn't matched!
					return [](const juce::String&, T...) {};
				}
				return this->_data;
			};
			
			operator const juce::String&()
			{
				return this->_typename;
			};

		private:
			JUCE_LEAK_DETECTOR(CallBackObject)
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
				std::make_shared<U>(func)
			);
			this->_lock.exitWrite();
		};

		template<typename ...T, class F = std::function<void(const juce::String&, T...)>, class U = JInterface::CallBackObject<T...>>
		void call(const juce::String& caller, const juce::String& key, T ...args)
		{
			this->_lock.enterRead();
			if (this->list.contains(key)) {
				U* obj = reinterpret_cast<U*>(this->list.getReference(key).get());
				const F& func = (*obj)();
				func(caller, args...);
			}
			this->_lock.exitRead();
		};
		
	private:
		juce::HashMap<juce::String, std::shared_ptr<CallBackObjectBase>> list;
		juce::ReadWriteLock _lock;
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JInterface)
	};
}
