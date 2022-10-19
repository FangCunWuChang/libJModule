#include "Interfaces.h"

namespace jmadf
{
	const StaticInterface* Interfaces::pStaticInterface = nullptr;

	void Interfaces::init(const StaticInterface* pStaticInterface)
	{
		Interfaces::pStaticInterface = pStaticInterface;
	}

	void Interfaces::destory()
	{
		Interfaces::pStaticInterface = nullptr;
	}

	void Interfaces::setLoadHook(const HookFunction& hook)
	{
		if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->setLoadHookFunc)
		{
			return;
		}
		Interfaces::pStaticInterface->setLoadHookFunc(ModuleStatics::getInfo()->ptrInfo->id, hook);
	}

	void Interfaces::setUnloadHook(const HookFunction& hook)
	{
		if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->setUnloadHookFunc)
		{
			return;
		}
		Interfaces::pStaticInterface->setUnloadHookFunc(ModuleStatics::getInfo()->ptrInfo->id, hook);
	}

	void Interfaces::setLoadCallback(const HookFunction& hook)
	{
		if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->setLoadCallbackFunc)
		{
			return;
		}
		Interfaces::pStaticInterface->setLoadCallbackFunc(ModuleStatics::getInfo()->ptrInfo->id, hook);
	}

	void Interfaces::setUnloadCallback(const HookFunction& hook)
	{
		if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->setUnloadCallbackFunc)
		{
			return;
		}
		Interfaces::pStaticInterface->setUnloadCallbackFunc(ModuleStatics::getInfo()->ptrInfo->id, hook);
	}
}
