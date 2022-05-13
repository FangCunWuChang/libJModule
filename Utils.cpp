#include "Utils.h"

const juce::String getComplieTime()
{
	juce::String cDate(__DATE__), cTime(__TIME__);
	juce::StringArray cDTS = juce::StringArray::fromTokens(cDate, " ", "");
	cDTS.getReference(0).swapWith(cDTS.getReference(2));
	cDTS.getReference(1).swapWith(cDTS.getReference(2));
	cDTS.addArray(juce::StringArray::fromTokens(cTime, ":", ""));

	const juce::StringArray mArray =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	int month = mArray.indexOf(cDTS[1]) + 1;
	juce::String sMonth = juce::String(month);
	cDTS.getReference(1).swapWith(sMonth);

	juce::String cDateTime;
	for (int i = 0; i < cDTS.size(); i++) {
		auto& str = cDTS[i];
		if (str.length() == 1) {
			cDateTime.append("0", 1);
		}
		cDateTime.append(str, str.length());
	}

	return cDateTime;
}
