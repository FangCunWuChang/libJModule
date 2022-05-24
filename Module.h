#pragma once
#include "JModuleBase.h"
#include "ModuleStatics.h"
#include "ModuleLoader.h"
#include "Exceptions.h"

namespace jmadf
{
	class Module : public JModuleBase
	{
		void initInfo(const ModuleInfo* info) override
		{
			ModuleStatics::init();
			ModuleStatics::getInfo()->ptrInfo = info;
		};
		
		void destoryInfo() override
		{
			ModuleStatics::destory();
		};

		void initLoader(const StaticInterface* staticInterface) override
		{
			ModuleLoader::init(staticInterface);
			Exceptions::init(staticInterface);
		};
		
		void destoryLoader() override
		{
			Exceptions::destory();
			ModuleLoader::destory();
		};
	};
}