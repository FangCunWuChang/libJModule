#pragma once
#include "JModuleBase.h"
#include "ModuleStatics.h"

namespace jmadf
{
	class Module : public JModuleBase
	{
		void initInfo(const ModuleInfo* info) override
		{
			ModuleStatics::init(info);
		};
		void destoryInfo() override
		{
			ModuleStatics::destory();
		};
	};
}