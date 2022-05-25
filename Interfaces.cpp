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
}
