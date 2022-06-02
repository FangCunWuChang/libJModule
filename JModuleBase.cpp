#include "JModuleBase.h"
#include "Utils.h"

namespace jmadf
{
	const juce::String JModuleBase::getModuleComplieTime(const juce::String& cDate, const juce::String& cTime)
	{
		return getComplieTime(cDate, cTime);
	}
}
