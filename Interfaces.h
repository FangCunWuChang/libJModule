﻿#pragma once
#include <JuceHeader.h>
#include "StaticInterface.h"
#include "ModuleStatics.h"
#include "Utils.h"

//提供给模块内部的接口管理类

namespace jmadf
{
	class Interfaces final
	{
	public:
		Interfaces() = delete;
		~Interfaces() = delete;

		static void init(const StaticInterface* pStaticInterface);
		static void destory();

		static void setLoadHook(const HookFunction& hook);
		static void setUnloadHook(const HookFunction& hook);
		static void setLoadCallback(const HookFunction& hook);
		static void setUnloadCallback(const HookFunction& hook);
		
		static const StaticInterface* pStaticInterface;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Interfaces)
	};

	template<typename ...T>
	class InterfacesDao final
	{
		using F = std::function<void(const juce::String&, T...)>;

		InterfacesDao() = delete;
		~InterfacesDao() = delete;

	public:
		static void regInterface(
			const juce::String& key, const F& func
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(
				ModuleStatics::getInfo()->ptrInfo->id
			);

			if (!pInterface) {
				return;
			}
			JInterfaceDao<T...>::set(pInterface, key, func);
		};

		static const std::function<void(T...)> getInterface(
			const juce::String& moduleId, const juce::String& key
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return [](T...) {};
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return [](T...) {};
			}
			return JInterfaceDao<T...>::get(pInterface, ModuleStatics::getInfo()->ptrInfo->id, key);
		};
		static bool checkInterface(
			const juce::String& moduleId, const juce::String& key
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return false;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return false;
			}
			return JInterfaceDao<T...>::check(pInterface, key);
		};

		static void callInterface(
			const juce::String& moduleId, const juce::String& key, T... args
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return;
			}
			JInterfaceDao<T...>::call(pInterface, ModuleStatics::getInfo()->ptrInfo->id, key, std::forward<T>(args)...);
		};
	};

	template<>
	class InterfacesDao<void> final
	{
		using F = std::function<void(const juce::String&)>;

		InterfacesDao() = delete;
		~InterfacesDao() = delete;

	public:
		static void regInterface(
			const juce::String& key, const F& func
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(
				ModuleStatics::getInfo()->ptrInfo->id
			);

			if (!pInterface) {
				return;
			}
			JInterfaceDao<void>::set(pInterface, key, func);
		};

		static const std::function<void(void)> getInterface(
			const juce::String& moduleId, const juce::String& key
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return [] {};
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return [] {};
			}
			return JInterfaceDao<void>::get(pInterface, ModuleStatics::getInfo()->ptrInfo->id, key);
		};
		static bool checkInterface(
			const juce::String& moduleId, const juce::String& key
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return false;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return false;
			}
			return JInterfaceDao<void>::check(pInterface, key);
		};

		static void callInterface(
			const juce::String& moduleId, const juce::String& key
		)
		{
			if (!Interfaces::pStaticInterface || !Interfaces::pStaticInterface->getInterfaceFunc)
			{
				return;
			}
			JInterface* pInterface = Interfaces::pStaticInterface->getInterfaceFunc(moduleId);
			if (!pInterface) {
				return;
			}
			JInterfaceDao<void>::call(pInterface, ModuleStatics::getInfo()->ptrInfo->id, key);
		};
	};
}