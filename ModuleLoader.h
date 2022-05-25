#pragma once
#include <JuceHeader.h>
#include "StaticInterface.h"

namespace jmadf
{
	class ModuleLoader final
	{
	public:
		ModuleLoader() = delete;
		~ModuleLoader() = delete;

		static void init(const StaticInterface* pStaticInterface);
		static void destory();

		static bool load(const juce::String& moduleId);
		static void unload(const juce::String& moduleId);

		static bool isLoaded(const juce::String& moduleId);
		static bool isExists(const juce::String& moduleId);

	private:
		static const StaticInterface* pStaticInterface;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModuleLoader)
	};
}
