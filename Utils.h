#pragma once
#include <JuceHeader.h>

//һЩ�����ķ���ʵ��

namespace jmadf
{
	const juce::String getComplieTime(const juce::String& cDate = __DATE__, const juce::String& cTime = __TIME__);
	const juce::String ptrToString(void* ptr);
}
