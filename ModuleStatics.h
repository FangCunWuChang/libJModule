#pragma once
#include "JModuleBase.h"
#include "StaticProperties.h"

//使用模板隔离模块具有特异化的静态信息

namespace jmadf
{	
	class ModuleStatics;
	namespace inside
	{
		//使用模板类以隔离不同模块静态成员
		template<class T>
		class ModuleStaticContainer final
		{
		public:
			static std::unique_ptr<StaticProperties> ptrInfo;
		};

		template<class T>
		std::unique_ptr<StaticProperties> ModuleStaticContainer<T>::ptrInfo = nullptr;
		
		//在JModuleInstance(className)宏实现上述隔离模板生成，此处进行方法声明
		class __MSC final
		{
			friend class jmadf::ModuleStatics;
			static void __InitStaticContainer();
			static void __DestoryStaticContainer();
			static StaticProperties* __GetPtr();
		};
	}

	//对上述方法进行封装
	class ModuleStatics final
	{
	public:
		static void init()
		{
			inside::__MSC::__InitStaticContainer();
		};
		
		static void destory()
		{
			inside::__MSC::__DestoryStaticContainer();
		};
		
		static StaticProperties* getInfo()
		{
			return inside::__MSC::__GetPtr();
		};
		
	};
}
