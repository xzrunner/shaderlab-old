#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class RoundedRectangle : public Node
{
public:
	RoundedRectangle()
		: Node("RoundedRectangle", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Width" },
			{ PINS_VECTOR1, "Height" },
			{ PINS_VECTOR1, "Radius" },
		},{
			{ PINS_VECTOR1, "Out", }
		}, true);
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_WIDTH,
		ID_HEIGHT,
		ID_RADIUS,
	};

	DECLARE_NODE_CLASS(RoundedRectangle)

}; // RoundedRectangle

}
}