#pragma once
#include "JModuleBase.h"
#include "ModuleStatics.h"
#include "ModuleLoader.h"
#include "Exceptions.h"
#include "Interfaces.h"

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
			Interfaces::init(staticInterface);
		};
		
		void destoryLoader() override
		{
			Interfaces::destory();
			Exceptions::destory();
			ModuleLoader::destory();
		};
	};
}