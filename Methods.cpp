#include "Methods.h"
#include "ModuleLoader.h"
#include "Exceptions.h"

namespace jmadf
{
	bool LoadModule(const juce::String& moduleId)
	{
		return ModuleLoader::load(moduleId);
	}
	
	void UnloadModule(const juce::String& moduleId)
	{
		ModuleLoader::unload(moduleId);
	}

	bool ModuleIsLoaded(const juce::String& moduleId)
	{
		return ModuleLoader::isLoaded(moduleId);
	}
	
	bool ModuleIsExists(const juce::String& moduleId)
	{
		return ModuleLoader::isExists(moduleId);
	}

	const juce::StringArray GetAllModules()
	{
		return ModuleLoader::getAll();
	}
	
	const juce::StringArray GetAllModulesInGroup(const juce::String& groupName)
	{
		return ModuleLoader::getAllInGroup(groupName);
	}

	const jmadf::ModuleInfo* FindModule(const juce::String& moduleId)
	{
		return ModuleLoader::find(moduleId);
	}

	void RaiseException(const juce::String& exception)
	{
		Exceptions::raiseException(exception);
	}
	
	const juce::String GetException()
	{
		return Exceptions::getException();
	}
	
	void ClearException()
	{
		Exceptions::clearException();
	}
}
