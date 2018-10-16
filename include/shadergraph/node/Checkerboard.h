#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Checkerboard : public Node
{
public:
	Checkerboard()
		: Node("Checkerboard", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_COLOR,   "Color A" },
			{ PINS_COLOR,   "Color B" },
			{ PINS_VECTOR2, "Frequency" },
		},{
			{ PINS_COLOR,   "Out", }
		});
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_COLOR_A,
		ID_COLOR_B,
		ID_FREQUENCY,
	};

	RTTR_ENABLE(Node)

}; // Checkerboard

}
}