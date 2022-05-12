#pragma once
#include <JuceHeader.h>

class JModuleBase
{
public:
	JModuleBase() = default;
	virtual ~JModuleBase() = default;

	virtual bool init() = 0;
	virtual void destory() = 0;

	virtual const juce::String getModuleName() = 0;
	virtual const juce::String getModuleVersion() = 0;
	const juce::String getModuleComplieTime();
	
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JModuleBase)
};

