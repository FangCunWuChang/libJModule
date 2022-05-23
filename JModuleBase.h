#pragma once
#include <JuceHeader.h>
#include "StaticInterface.h"
#include "ModuleInfo.h"

class JModule;

namespace jmadf {
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
		friend class ::JModule;
		void initLoader(const StaticInterface* staticInterface);
		void destoryLoader();
		
	protected:
		virtual void initInfo(const ModuleInfo* info) = 0;
		virtual void destoryInfo() = 0;
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JModuleBase)
	};
}
