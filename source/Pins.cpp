#include "shadergraph/Pins.h"

namespace
{

const pt2::Color COL_DEFAULT   = pt2::Color(255, 255, 255);

const pt2::Color COL_VECTOR1   = pt2::Color(132, 228, 231);
const pt2::Color COL_VECTOR2   = pt2::Color(154, 239, 146);
const pt2::Color COL_VECTOR3   = pt2::Color(246, 255, 154);
const pt2::Color COL_VECTOR4   = pt2::Color(251, 203, 244);
const pt2::Color COL_COLOR     = pt2::Color(251, 203, 244);
const pt2::Color COL_TEXTURE2D = pt2::Color(255, 139, 139);
const pt2::Color COL_BOOLEAN   = pt2::Color(148, 129, 230);

}

namespace sg
{

Pins::Pins(bool is_input, int pos, int type, const std::string& name, const bp::Node& parent)
	: bp::Pins(is_input, pos, type, name, parent)
{
}

std::string Pins::GetDesc() const
{
	std::string ret = GetName();
	switch (GetType())
	{
	case PINS_VECTOR1:
	case PINS_DYNAMIC_VECTOR:
		ret += "(1)";
		break;
	case PINS_VECTOR2:
		ret += "(2)";
		break;
	case PINS_VECTOR3:
		ret += "(3)";
		break;
	case PINS_VECTOR4:
		ret += "(4)";
		break;
	case PINS_COLOR:
		ret += "(4)";
		break;
	case PINS_TEXTURE2D:
		ret += "(T2)";
		break;
	case PINS_BOOLEAN:
		ret += "(B)";
		break;
	}
	return ret;
}

const pt2::Color& Pins::GetColor() const
{
	switch (GetType())
	{
	case PINS_VECTOR1:
	case PINS_DYNAMIC_VECTOR:
		return COL_VECTOR1;
	case PINS_VECTOR2:
		return COL_VECTOR2;
	case PINS_VECTOR3:
		return COL_VECTOR3;
	case PINS_VECTOR4:
		return COL_VECTOR4;
	case PINS_COLOR:
		return COL_COLOR;
	case PINS_TEXTURE2D:
		return COL_TEXTURE2D;
	case PINS_BOOLEAN:
		return COL_BOOLEAN;
	default:
		return COL_DEFAULT;
	}
}

bool Pins::CanTypeCast(int type) const
{
	if (GetType() == type) {
		return true;
	}

	switch (GetType())
	{
	case PINS_DYNAMIC_VECTOR:
		return type == PINS_VECTOR1
			|| type == PINS_VECTOR2
			|| type == PINS_VECTOR3
			|| type == PINS_VECTOR4
			|| type == PINS_COLOR
			|| type == PINS_BOOLEAN;
	case PINS_VECTOR1:
		return type == PINS_DYNAMIC_VECTOR
			|| type == PINS_VECTOR2
			|| type == PINS_VECTOR3
			|| type == PINS_VECTOR4
			|| type == PINS_COLOR
			|| type == PINS_BOOLEAN;
	case PINS_VECTOR2:
		return type == PINS_DYNAMIC_VECTOR
			|| type == PINS_VECTOR1
			|| type == PINS_VECTOR3
			|| type == PINS_VECTOR4
			|| type == PINS_COLOR;
	case PINS_VECTOR3:
		return type == PINS_DYNAMIC_VECTOR
			|| type == PINS_VECTOR1
			|| type == PINS_VECTOR2
			|| type == PINS_VECTOR4
			|| type == PINS_COLOR;
	case PINS_VECTOR4:
		return type == PINS_DYNAMIC_VECTOR
			|| type == PINS_VECTOR1
			|| type == PINS_VECTOR2
			|| type == PINS_VECTOR3
			|| type == PINS_COLOR;
	case PINS_COLOR:
		return type == PINS_DYNAMIC_VECTOR
			|| type == PINS_VECTOR1
			|| type == PINS_VECTOR2
			|| type == PINS_VECTOR3
			|| type == PINS_VECTOR4;
	case PINS_TEXTURE2D:
		return false;
	case PINS_BOOLEAN:
		return type == PINS_DYNAMIC_VECTOR
			|| type == PINS_VECTOR1;
	}

	return false;
}

}