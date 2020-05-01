#include "shaderlab/PinCallback.h"
#include "shaderlab/PinType.h"

#include <painting0/Color.h>
#include <blueprint/Pin.h>

#include <string>

namespace
{

const pt0::Color COL_DEFAULT   = pt0::Color(255, 255, 255);

const pt0::Color COL_VECTOR1   = pt0::Color(132, 228, 231);
const pt0::Color COL_VECTOR2   = pt0::Color(154, 239, 146);
const pt0::Color COL_VECTOR3   = pt0::Color(246, 255, 154);
const pt0::Color COL_VECTOR4   = pt0::Color(251, 203, 244);
const pt0::Color COL_COLOR     = pt0::Color(251, 203, 244);
const pt0::Color COL_TEXTURE2D = pt0::Color(255, 139, 139);
const pt0::Color COL_BOOLEAN   = pt0::Color(148, 129, 230);

std::string get_desc_func(const std::string& name, int type)
{
	std::string ret = name;
	switch (type)
	{
    case shaderlab::PIN_VECTOR1:
	case shaderlab::PIN_DYNAMIC_VECTOR:
		ret += "(1)";
		break;
	case shaderlab::PIN_VECTOR2:
		ret += "(2)";
		break;
	case shaderlab::PIN_VECTOR3:
		ret += "(3)";
		break;
	case shaderlab::PIN_VECTOR4:
		ret += "(4)";
		break;
	case shaderlab::PIN_COLOR:
		ret += "(4)";
		break;
	case shaderlab::PIN_TEXTURE2D:
		ret += "(T2)";
		break;
	case shaderlab::PIN_BOOLEAN:
		ret += "(B)";
		break;
	}
	return ret;
}

const pt0::Color& get_color_func(int type)
{
	switch (type)
	{
	case shaderlab::PIN_VECTOR1:
	case shaderlab::PIN_DYNAMIC_VECTOR:
		return COL_VECTOR1;
	case shaderlab::PIN_VECTOR2:
		return COL_VECTOR2;
	case shaderlab::PIN_VECTOR3:
		return COL_VECTOR3;
	case shaderlab::PIN_VECTOR4:
		return COL_VECTOR4;
	case shaderlab::PIN_COLOR:
		return COL_COLOR;
	case shaderlab::PIN_TEXTURE2D:
		return COL_TEXTURE2D;
	case shaderlab::PIN_BOOLEAN:
		return COL_BOOLEAN;
	default:
		return COL_DEFAULT;
	}
}

bool can_type_cast_func(int type_from, int type_to)
{
	if (type_from == type_to) {
		return true;
	}
	if (type_to == shaderlab::PIN_FUNCTION) {
		return true;
	}
    if (type_from == bp::PIN_ANY_VAR ||
        type_to == bp::PIN_ANY_VAR) {
        return true;
    }

	switch (type_from)
	{
	case shaderlab::PIN_DYNAMIC_VECTOR:
		return type_to == shaderlab::PIN_VECTOR1
			|| type_to == shaderlab::PIN_VECTOR2
			|| type_to == shaderlab::PIN_VECTOR3
			|| type_to == shaderlab::PIN_VECTOR4
			|| type_to == shaderlab::PIN_COLOR
			|| type_to == shaderlab::PIN_BOOLEAN;
	case shaderlab::PIN_VECTOR1:
		return type_to == shaderlab::PIN_DYNAMIC_VECTOR
			|| type_to == shaderlab::PIN_VECTOR2
			|| type_to == shaderlab::PIN_VECTOR3
			|| type_to == shaderlab::PIN_VECTOR4
			|| type_to == shaderlab::PIN_COLOR
			|| type_to == shaderlab::PIN_BOOLEAN;
	case shaderlab::PIN_VECTOR2:
		return type_to == shaderlab::PIN_DYNAMIC_VECTOR
			|| type_to == shaderlab::PIN_VECTOR1
			|| type_to == shaderlab::PIN_VECTOR3
			|| type_to == shaderlab::PIN_VECTOR4
			|| type_to == shaderlab::PIN_COLOR;
	case shaderlab::PIN_VECTOR3:
		return type_to == shaderlab::PIN_DYNAMIC_VECTOR
			|| type_to == shaderlab::PIN_VECTOR1
			|| type_to == shaderlab::PIN_VECTOR2
			|| type_to == shaderlab::PIN_VECTOR4
			|| type_to == shaderlab::PIN_COLOR;
	case shaderlab::PIN_VECTOR4:
		return type_to == shaderlab::PIN_DYNAMIC_VECTOR
			|| type_to == shaderlab::PIN_VECTOR1
			|| type_to == shaderlab::PIN_VECTOR2
			|| type_to == shaderlab::PIN_VECTOR3
			|| type_to == shaderlab::PIN_COLOR;
	case shaderlab::PIN_COLOR:
		return type_to == shaderlab::PIN_DYNAMIC_VECTOR
			|| type_to == shaderlab::PIN_VECTOR1
			|| type_to == shaderlab::PIN_VECTOR2
			|| type_to == shaderlab::PIN_VECTOR3
			|| type_to == shaderlab::PIN_VECTOR4;
	case shaderlab::PIN_TEXTURE2D:
		return false;
	case shaderlab::PIN_BOOLEAN:
		return type_to == shaderlab::PIN_DYNAMIC_VECTOR
			|| type_to == shaderlab::PIN_VECTOR1;
	case shaderlab::PIN_DYNAMIC_MATRIX:
		return type_to == shaderlab::PIN_MATRIX2
			|| type_to == shaderlab::PIN_MATRIX3
			|| type_to == shaderlab::PIN_MATRIX4;
	case shaderlab::PIN_MATRIX2:
		return type_to == shaderlab::PIN_DYNAMIC_MATRIX
			|| type_to == shaderlab::PIN_MATRIX3
			|| type_to == shaderlab::PIN_MATRIX4;
	case shaderlab::PIN_MATRIX3:
		return type_to == shaderlab::PIN_DYNAMIC_MATRIX
			|| type_to == shaderlab::PIN_MATRIX2
			|| type_to == shaderlab::PIN_MATRIX4;
	case shaderlab::PIN_MATRIX4:
		return type_to == shaderlab::PIN_DYNAMIC_MATRIX
			|| type_to == shaderlab::PIN_MATRIX2
			|| type_to == shaderlab::PIN_MATRIX3;
	}

	return false;
}

}

namespace shaderlab
{

void InitPinCallback()
{
    bp::Pin::SetExtendFuncs({
        get_desc_func,
        get_color_func,
        can_type_cast_func
    });
}

}