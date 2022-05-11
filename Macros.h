#pragma once

#ifdef _MSC_VER
#define JMExport __declspec(dllexport)
#endif

#ifdef __clang__
#define JMExport __declspec(dllexport)
#endif

#ifdef __GNUC__
#define JMExport __attribute__((visibility("default")))
#endif

#if ! (defined (_MSC_VER) || defined (__clang__) || defined (__GNUC__))
#define JMExport 
#endif

#define JMCall _cdecl