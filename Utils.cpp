#include "Utils.h"

namespace jmadf
{
	const juce::String getComplieTime(const juce::String& cDate, const juce::String& cTime)
	{
		juce::StringArray cDTS = juce::StringArray::fromTokens(cDate, " ", "");
		cDTS.addArray(juce::StringArray::fromTokens(cTime, ":", ""));

		for (int i = 0; i < cDTS.size();) {
			if (cDTS[i].isEmpty()) {
				cDTS.remove(i);
				continue;
			}
			i++;
		}
		
		cDTS.getReference(0).swapWith(cDTS.getReference(2));
		cDTS.getReference(1).swapWith(cDTS.getReference(2));

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

	const juce::String ptrToString(void* ptr)
	{
		size_t ptrN = reinterpret_cast<size_t>(ptr);
		juce::String str("0x");
		str += juce::String::toHexString<size_t>(ptrN);
		return str;
	}
}
