#include "ModuleLoader.h"
#include "ModuleStatics.h"

namespace jmadf
{
	const StaticInterface* ModuleLoader::pStaticInterface = nullptr;

	void ModuleLoader::init(const StaticInterface* pStaticInterface)
	{
		ModuleLoader::pStaticInterface = pStaticInterface;
	}

	void ModuleLoader::destory()
	{
		ModuleLoader::pStaticInterface = nullptr;
	}

	bool ModuleLoader::load(const juce::String& moduleId)
	{
		if (ModuleStatics::getInfo()->ptrInfo->id == moduleId) {
			jassertfalse;//Module couldn't load itself!
			return false;
		}
		if (!ModuleLoader::pStaticInterface || !ModuleLoader::pStaticInterface->loadFunc)
		{
			return false;
		}
		return ModuleLoader::pStaticInterface->loadFunc(moduleId);
	}
	
	void ModuleLoader::unload(const juce::String& moduleId)
	{
		if (ModuleStatics::getInfo()->ptrInfo->id == moduleId) {
			jassertfalse;//Module couldn't unload itself!
			return;
		}
		if (!ModuleLoader::pStaticInterface || !ModuleLoader::pStaticInterface->unloadFunc)
		{
			return;
		}
		ModuleLoader::pStaticInterface->unloadFunc(moduleId);
	}

	bool ModuleLoader::isLoaded(const juce::String& moduleId)
	{
		if (!ModuleLoader::pStaticInterface || !ModuleLoader::pStaticInterface->isLoadedFunc)
		{
			return false;
		}
		return ModuleLoader::pStaticInterface->isLoadedFunc(moduleId);
	}
	
	bool ModuleLoader::isExists(const juce::String& moduleId)
	{
		if (!ModuleLoader::pStaticInterface || !ModuleLoader::pStaticInterface->isExistsFunc)
		{
			return false;
		}
		return ModuleLoader::pStaticInterface->isExistsFunc(moduleId);
	}
}
