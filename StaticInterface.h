#pragma once
#include <JuceHeader.h>
#include "JInterface.h"

namespace jmadf
{
	class StaticInterface final
	{
	public:
		StaticInterface() = default;
		~StaticInterface() = default;

		bool (*loadFunc)(const juce::String&) = nullptr;
		void (*unloadFunc)(const juce::String&) = nullptr;

		bool (*isLoadedFunc)(const juce::String&) = nullptr;
		bool (*isExistsFunc)(const juce::String&) = nullptr;

		void (*raiseExceptionFunc)(const juce::String&) = nullptr;
		const juce::String (*getExceptionFunc)() = nullptr;
		void (*clearExceptionFunc)() = nullptr;

		JInterface* (*getInterfaceFunc)(const juce::String&) = nullptr;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticInterface)
	};
}
