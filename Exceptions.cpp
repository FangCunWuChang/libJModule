#include "Exceptions.h"
#include "ModuleStatics.h"

namespace jmadf
{
	const StaticInterface* Exceptions::pStaticInterface = nullptr;

	void Exceptions::init(const StaticInterface* pStaticInterface)
	{
		Exceptions::pStaticInterface = pStaticInterface;
	}

	void Exceptions::destory()
	{
		Exceptions::pStaticInterface = nullptr;
	}
	
	void Exceptions::raiseException(const juce::String& exception)
	{
		if (!Exceptions::pStaticInterface || !Exceptions::pStaticInterface->raiseExceptionFunc)
		{
			return;
		}
		Exceptions::pStaticInterface->raiseExceptionFunc(
			"[" + ModuleStatics::getInfo()->ptrInfo->id + "]" + exception
		);
	}

	const juce::String Exceptions::getException()
	{
		if (!Exceptions::pStaticInterface || !Exceptions::pStaticInterface->getExceptionFunc)
		{
			return "";
		}
		return Exceptions::pStaticInterface->getExceptionFunc();
	}

	void Exceptions::clearException()
	{
		if (!Exceptions::pStaticInterface || !Exceptions::pStaticInterface->clearExceptionFunc)
		{
			return;
		}
		Exceptions::pStaticInterface->clearExceptionFunc();
	}
}