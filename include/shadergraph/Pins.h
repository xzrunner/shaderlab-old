#pragma once

#include <blueprint/Pins.h>

namespace shadergraph
{

enum PinsType
{
	PINS_VECTOR1 = 1000,
	PINS_VECTOR2,
	PINS_VECTOR3,
	PINS_VECTOR4,
	PINS_COLOR,
	PINS_TEXTURE2D,
	PINS_BOOLEAN,

}; // PinsType

class Pins : public bp::node::Pins
{
public:
	Pins(bool is_input, int pos, int type, const std::string& name,
		const bp::node::Node& parent);

	virtual std::string GetDesc() const;
	virtual const pt2::Color& GetColor() const;

	virtual bool CanTypeCast(int type) const;

}; // Pins

}