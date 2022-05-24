#pragma once
#include <JuceHeader.h>
#include "ModuleInfo.h"

namespace jmadf
{
	class StaticProperties final
	{
		public:
			StaticProperties() = default;
			~StaticProperties() = default;
			
			const ModuleInfo* ptrInfo = nullptr;
			
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticProperties)
	};
}