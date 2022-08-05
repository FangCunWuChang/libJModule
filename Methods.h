#pragma once
#include <JuceHeader.h>
#include "ModuleInfo.h"
#include "Interfaces.h"

//对模块开放的接口，推荐在模块里使用这些接口使用框架功能

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
		InterfacesDao<T...>::regInterface(key, func);
	};

	template<typename ...T>
	const std::function<void(T...)> GetInterface(
		const juce::String& moduleId, const juce::String& key
	)
	{
		return InterfacesDao<T...>::getInterface(moduleId, key);
	};

	template<typename ...T>
	void CallInterface(
		const juce::String& moduleId, const juce::String& key, T... args
	)
	{
		InterfacesDao<T...>::callInterface(moduleId, key, args...);
	};

	template<typename ...T>
	requires std::is_void_v<T...>
	void CallInterface(
		const juce::String& moduleId, const juce::String& key
	)
	{
		InterfacesDao<T...>::callInterface(moduleId, key);
	};

	const ModuleInfo* GetModuleInfo();
}
