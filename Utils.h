#pragma once
#include <JuceHeader.h>

//一些基础的方法实现

namespace jmadf
{
	const juce::String getComplieTime(const juce::String& cDate = __DATE__, const juce::String& cTime = __TIME__);
	const juce::String ptrToString(void* ptr);
}
