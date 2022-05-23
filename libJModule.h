#pragma once
#include "Macros.h"
#include "Module.h"
#include "ModuleStatics.h"

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

#define JModuleMSCInstance(className) \
namespace jmadf { namespace inside { \
	void __MSC::__InitStaticContainer(const ModuleInfo* ptrInfo) \
	{ \
		ModuleStaticContainer<className>::ptrInfo = ptrInfo; \
	} \
	void __MSC::__DestoryStaticContainer() \
	{ \
		ModuleStaticContainer<className>::ptrInfo = nullptr; \
	} \
	const ModuleInfo* __MSC::__GetPtr() \
	{ \
		return ModuleStaticContainer<className>::ptrInfo; \
	} \
}} 

#define JModuleInstance(className) \
JModuleCreateInstance(className) \
JModuleDestroyInstance(className) \
JModuleMSCInstance(className)
