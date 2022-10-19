#pragma once
#include <JuceHeader.h>
#include "JInterface.h"
#include "ModuleInfo.h"
#include "Utils.h"

//传入给模块的框架功能接口

namespace jmadf
{
	class StaticInterface final
	{
	public:
		StaticInterface() = default;
		~StaticInterface() = default;

		bool (*loadFunc)(const juce::String&, const juce::String&) = nullptr;
		void (*unloadFunc)(const juce::String&, const juce::String&) = nullptr;

		bool (*isLoadedFunc)(const juce::String&) = nullptr;
		bool (*isExistsFunc)(const juce::String&) = nullptr;

		const juce::StringArray (*getAllFunc)() = nullptr;
		const juce::StringArray (*getAllInGroupFunc)(const juce::String&) = nullptr;

		const jmadf::ModuleInfo* (*findFunc)(const juce::String&) = nullptr;

		void (*raiseExceptionFunc)(const juce::String&) = nullptr;
		const juce::String (*getExceptionFunc)() = nullptr;
		void (*clearExceptionFunc)() = nullptr;

		void (*setLoadHookFunc)(const juce::String&, const HookFunction&) = nullptr;
		void (*setUnloadHookFunc)(const juce::String&, const HookFunction&) = nullptr;
		void (*setLoadCallbackFunc)(const juce::String&, const HookFunction&) = nullptr;
		void (*setUnloadCallbackFunc)(const juce::String&, const HookFunction&) = nullptr;

		JInterface* (*getInterfaceFunc)(const juce::String&) = nullptr;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticInterface)
	};
}
