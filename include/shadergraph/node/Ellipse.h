#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Ellipse : public Node
{
public:
	Ellipse()
		: Node("Ellipse", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Width" },
			{ PINS_VECTOR1, "Height" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_WIDTH,
		ID_HEIGHT,
	};

	RTTR_ENABLE(Node)

}; // Ellipse

}
}