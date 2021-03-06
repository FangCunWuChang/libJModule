#pragma once
#include <JuceHeader.h>

//ģ????Ϣ

namespace jmadf
{
	class ModuleInfo final
	{
	public:
		ModuleInfo() = default;
		~ModuleInfo() = default;

		juce::String id;//"developer.moduleName"
		juce::String version;//"x.x.x"
		juce::String group;//"productName.groupName"
		juce::String productId;//"{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}"
		juce::String path;//"D:/xxxxxx/module/developer.moduleName"
		juce::String entry;//"developer.moduleName"
		juce::String infoList;//"developer.moduleName.json"
		juce::StringArray dependencies;//??????id
		juce::String description;//????

	private:
		JUCE_LEAK_DETECTOR(ModuleInfo)
	};
}


