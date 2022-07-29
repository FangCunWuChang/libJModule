#pragma once
#include "JModuleBase.h"
#include "ModuleStatics.h"
#include "ModuleLoader.h"
#include "Exceptions.h"
#include "Interfaces.h"

//所有模块类的共同基类，但不会对JMADF主程序暴露
//在这里编写模块共有的接口，但需要对不同模块进行特异化的部分

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

		void destoryInterfaces(JInterface* interfaces) override
		{
			delete interfaces;
		};
	};
}