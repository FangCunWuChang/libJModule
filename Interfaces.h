#pragma once
#include <JuceHeader.h>
#include "StaticInterface.h"
#include "ModuleStatics.h"

namespace jmadf
{
	class Interfaces final
	{
	public:
		Interfaces() = delete;
		~Interfaces() = delete;

		static void init(const StaticInterface* pStaticInterface);
		static void destory();

		template<typename ...T, class F = std::function<void(const juce::String&, T...)>>
		static void regInterface(
			const juce::String& key, const F& func
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(
				ModuleStatics::getInfo()->ptrInfo->id
			);
			
			if (!pInterface) {
				return;
			}
			pInterface->set<T...>(key, func);
		};
		
		template<typename ...T>
		static void callInterface(
			const juce::String& moduleId, const juce::String& key, T... args
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return;
			}
			pInterface->call<T...>(ModuleStatics::getInfo()->ptrInfo->id, key, args...);
		};

		template<typename ...T>
		requires jmadf::IsVoid<T...>
		static void callInterface(
			const juce::String& moduleId, const juce::String& key
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return;
			}
			pInterface->call<T...>(ModuleStatics::getInfo()->ptrInfo->id, key);
		};
		
	private:
		static const StaticInterface* pStaticInterface;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Interfaces)
	};
}