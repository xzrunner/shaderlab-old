#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class TextureSample : public Node
{
public:
	TextureSample()
		: Node("TextureSample", true)
	{
		AddPins(std::make_shared<Pins>(true, 0, PINS_TEXTURE2D, "Tex", *this));
		AddPins(std::make_shared<Pins>(true, 1, PINS_VECTOR2,   "UV", *this));

		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR4, "RGBA", *this));
		AddPins(std::make_shared<Pins>(false, 1, PINS_VECTOR1, "R", *this));
		AddPins(std::make_shared<Pins>(false, 2, PINS_VECTOR1, "G", *this));
		AddPins(std::make_shared<Pins>(false, 3, PINS_VECTOR1, "B", *this));
		AddPins(std::make_shared<Pins>(false, 4, PINS_VECTOR1, "A", *this));

		Layout();
	}

public:
	enum InputId
	{
		ID_TEX = 0,
		ID_UV,
	};

	enum OutputId
	{
		ID_RGBA = 0,
		ID_R,
		ID_G,
		ID_B,
		ID_A,
	};

	DECLARE_NODE_CLASS(TextureSample)

}; // TextureSample

}
}