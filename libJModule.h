#pragma once
#include "Macros.h"
#include "JModuleBase.h"

extern "C" JMExport JModuleBase* JMCall JModuleCreateInstance();

#define JModuleCreateInstance(className) \
JModuleBase* JModuleCreateInstance() {return new (className);}
