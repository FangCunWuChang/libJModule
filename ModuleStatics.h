#pragma once
#include "JModuleBase.h"
#include "ModuleInfo.h"

namespace jmadf
{
	//使用模板类以隔离不同模块静态成员
	template<class T>
	class ModuleStaticContainer final
	{
	public:
		static const ModuleInfo* ptrInfo;
	};

	template<class T>
	const ModuleInfo* ModuleStaticContainer<T>::ptrInfo = nullptr;
	
	//在JModuleInstance(className)宏实现上述隔离模板生成，此处进行方法声明
	class ModuleStatics;
	namespace inside
	{
		class __MSC final
		{
			friend class jmadf::ModuleStatics;
			static void __InitStaticContainer(const ModuleInfo* ptrInfo);
			static void __DestoryStaticContainer();
			static const ModuleInfo* __GetPtr();
		};
	}

	//对上述方法进行封装
	class ModuleStatics final
	{
	public:
		static void init(const ModuleInfo* ptrInfo)
		{
			inside::__MSC::__InitStaticContainer(ptrInfo);
		};
		
		static void destory()
		{
			inside::__MSC::__DestoryStaticContainer();
		};
		
		static const ModuleInfo* getInfo()
		{
			return inside::__MSC::__GetPtr();
		};
		
	};
}
