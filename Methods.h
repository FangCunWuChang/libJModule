#pragma once
#include <JuceHeader.h>
#include "ModuleInfo.h"
#include "Interfaces.h"

namespace jmadf
{
	bool LoadModule(const juce::String& moduleId);
	void UnloadModule(const juce::String& moduleId);

	bool ModuleIsLoaded(const juce::String& moduleId);
	bool ModuleIsExists(const juce::String& moduleId);

	const juce::StringArray GetAllModules();
	const juce::StringArray GetAllModulesInGroup(const juce::String& groupName);

	const jmadf::ModuleInfo* FindModule(const juce::String& moduleId);
	
	void RaiseException(const juce::String& exception);
	const juce::String GetException();
	void ClearException();
	
	template<typename ...T, class F = std::function<void(const juce::String&, T...)>>
	void RegisterInterface(
		const juce::String& key, const F& func
	)
	{
		Interfaces::regInterface<T...>(key, func);
	};

	template<typename ...T>
	void CallInterface(
		const juce::String& moduleId, const juce::String& key, T... args
	)
	{
		Interfaces::callInterface<T...>(moduleId, key, args...);
	};

	template<typename ...T>
	requires IsVoid<T...>
	void CallInterface(
		const juce::String& moduleId, const juce::String& key
	)
	{
		Interfaces::callInterface<T...>(moduleId, key);
	};

	const ModuleInfo* GetModuleInfo();
}
