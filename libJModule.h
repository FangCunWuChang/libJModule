#pragma once
#include "Macros.h"
#include "Module.h"
#include "ModuleStatics.h"
#include "Methods.h"

//声明模块的实例创建与销毁函数，这些函数会被暴露于模块文件用于系统加载模块
//这些函数是JMADF模块的入口点
//提供相关函数的实现宏

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
	void __MSC::__InitStaticContainer() \
	{ \
		ModuleStaticContainer<className>::ptrInfo = std::make_unique<StaticProperties>(); \
	} \
	void __MSC::__DestoryStaticContainer() \
	{ \
		ModuleStaticContainer<className>::ptrInfo = nullptr; \
	} \
	StaticProperties* __MSC::__GetPtr() \
	{ \
		return ModuleStaticContainer<className>::ptrInfo.get(); \
	} \
}} 

#define JModuleInstance(className) \
JModuleCreateInstance(className) \
JModuleDestroyInstance(className) \
JModuleMSCInstance(className)
