#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Combine : public Node
{
public:
	Combine()
		: Node("Combine", true)
	{
		InitPins({
			{ PINS_VECTOR1, "R" },
			{ PINS_VECTOR1, "G" },
			{ PINS_VECTOR1, "B" },
			{ PINS_VECTOR1, "A" },
		},{
			{ PINS_VECTOR4, "RGBA" },
			{ PINS_VECTOR3, "RGB" },
			{ PINS_VECTOR2, "RG" },
		});
	}

public:
	enum InputID
	{
		ID_R = 0,
		ID_G,
		ID_B,
		ID_A,
	};

	enum OutputID
	{
		ID_RGBA = 0,
		ID_RGB,
		ID_RG,
	};

	RTTR_ENABLE(Node)

}; // Combine

}
}