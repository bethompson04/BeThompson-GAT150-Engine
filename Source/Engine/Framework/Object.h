#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(className) \
	virtual const char* GetClassName() {return #className;} \
	virtual void Read(const json_t& value); \
	virtual std::unique_ptr<Object>Clone() { return std::make_unique<className>(*this); } \
	class Register \
	{ \
	public: \
		Register() \
		{ \
			Factory::Instance().Register<className>(#className); \
		} \
	};

#define CLASS_DEFINITION(className) \
	className::Register register_class;

namespace MEN
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}

		virtual ~Object() { OnDestroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	public:
		std::string name;
		bool active = true;
	};
}