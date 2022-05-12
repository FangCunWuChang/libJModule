#pragma once
#include "Macros.h"
#include "JModuleBase.h"

extern "C" JMExport JModuleBase* JMCall JModuleCreateInstance();

extern "C" JMExport void JMCall JModuleDestroyInstance(JModuleBase* p);

#define JModuleCreateInstance(className) \
JModuleBase* JModuleCreateInstance() {return new (className);}

#define JModuleDestroyInstance(className) \
void JModuleDestroyInstance(JModuleBase* p) {delete reinterpret_cast<className*>(p); }

#define JModuleInstance(className) \
JModuleCreateInstance(className) \
JModuleDestroyInstance(className)
