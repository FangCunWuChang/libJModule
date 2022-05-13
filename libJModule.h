#pragma once
#include "Macros.h"
#include "JModuleBase.h"

extern "C" JMExport jmadf::JModuleBase* JMCall JModuleCreateInstance();

extern "C" JMExport void JMCall JModuleDestroyInstance(const jmadf::JModuleBase* pInstance);

#define JModuleCreateInstance(className) \
jmadf::JModuleBase* JModuleCreateInstance() \
{ \
	return new(std::nothrow) (className); \
}

#define JModuleDestroyInstance(className) \
void JModuleDestroyInstance(const jmadf::JModuleBase* p) \
{ \
	delete reinterpret_cast<className*>(const_cast<jmadf::JModuleBase*>(p)); \
}

#define JModuleInstance(className) \
JModuleCreateInstance(className) \
JModuleDestroyInstance(className)
