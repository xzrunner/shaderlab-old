#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Polygon : public Node
{
public:
	Polygon()
		: Node("Polygon", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Sides" },
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
		ID_SIDES,
		ID_WIDTH,
		ID_HEIGHT,
	};

	RTTR_ENABLE(Node)

}; // Polygon

}
}