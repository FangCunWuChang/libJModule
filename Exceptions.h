#pragma once
#include <JuceHeader.h>
#include "StaticInterface.h"

//提供给模块内部的异常类

namespace jmadf
{
	class Exceptions final
	{
	public:
		Exceptions() = delete;
		~Exceptions() = delete;

		static void init(const StaticInterface* pStaticInterface);
		static void destory();

		static void raiseException(const juce::String& exception);
		static const juce::String getException();
		static void clearException();

	private:
		static const StaticInterface* pStaticInterface;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Exceptions)
	};
}
