#pragma once

#include <blueprint/Pins.h>

namespace sg
{

enum PinsType
{
	PINS_BOOLEAN = 1000,
	PINS_DYNAMIC_VECTOR,
	PINS_VECTOR1,
	PINS_VECTOR2,
	PINS_VECTOR3,
	PINS_VECTOR4,
	PINS_COLOR,
	PINS_TEXTURE2D,
	PINS_CUBE_MAP,
	PINS_DYNAMIC_MATRIX,
	PINS_MATRIX2,
	PINS_MATRIX3,
	PINS_MATRIX4,
	PINS_FUNCTION,

}; // PinsType

class Pins : public bp::Pins
{
public:
	Pins(bool is_input, int pos, int type, const std::string& name,
		const bp::Node& parent);

	virtual std::string GetDesc() const;
	virtual const pt2::Color& GetColor() const;

	virtual bool CanTypeCast(int type) const;

}; // Pins

}