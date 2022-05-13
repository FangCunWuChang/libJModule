#include "JModuleBase.h"
#include "Utils.h"
#include "ModuleLoader.h"

namespace jmadf {
	const juce::String JModuleBase::getModuleComplieTime()
	{
		return ::getComplieTime();
	}
	
	void JModuleBase::initLoader(const StaticInterface* staticInterface)
	{
		ModuleLoader::init(staticInterface);
	}
	
	void JModuleBase::destoryLoader()
	{
		ModuleLoader::destory();
	}
}
