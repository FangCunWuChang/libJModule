﻿#pragma once

//平台和编译器相关的宏定义

#ifdef _MSC_VER
#define JMExport __declspec(dllexport)
#define JMCall _cdecl
#endif

#ifdef __clang__
#define JMExport __attribute__((visibility("default")))
#define JMCall
#endif

#ifdef __GNUC__
#define JMExport __attribute__((visibility("default")))
#define JMCall
#endif

#if ! (defined (_MSC_VER) || defined (__clang__) || defined (__GNUC__))
#define JMExport 
#define JMCall
#endif
