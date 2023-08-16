#include "Object.h"

namespace MEN
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}