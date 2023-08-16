#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(className) \
	virtual const char* GetClassName() {return #className;} \
	void Read(const json_t& value); \
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

	protected:
		std::string name;
	};
}