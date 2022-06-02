#pragma once
#include <JuceHeader.h>
#include "StaticInterface.h"
#include "ModuleInfo.h"

class JModule;

namespace jmadf
{
	//此类中内容会暴露至主程序，应严格注意
	//请将必须实现的内容派生至jmadf::Module中实现
	class JModuleBase
	{
	public:
		JModuleBase() = default;
		virtual ~JModuleBase() = default;

		virtual bool init() = 0;
		virtual void destory() = 0;

		virtual const juce::String getModuleName() = 0;
		virtual const juce::String getModuleVersion() = 0;
		const juce::String getModuleComplieTime(const juce::String& cDate = __DATE__, const juce::String& cTime = __TIME__);
		
	protected:
		friend class ::JModule;

		virtual void initInfo(const ModuleInfo* info) = 0;
		virtual void destoryInfo() = 0;

		virtual void initLoader(const StaticInterface* staticInterface) = 0;
		virtual void destoryLoader() = 0;
		
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JModuleBase)
	};
}
