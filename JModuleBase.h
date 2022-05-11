#pragma once
#include <JuceHeader.h>

class JModuleBase
{
public:
	JModuleBase() = default;
	virtual ~JModuleBase() = default;
	
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JModuleBase)
};

