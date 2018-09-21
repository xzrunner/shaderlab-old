#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Rectangle : public Node
{
public:
	Rectangle()
		: Node("Rectangle", true)
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

	DECLARE_NODE_CLASS(Rectangle)

}; // Rectangle

}
}