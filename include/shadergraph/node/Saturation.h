#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Saturation : public Node
{
public:
	Saturation()
		: Node("Saturation", true)
	{
		InitPins({
			{ PINS_VECTOR3, "In" },
			{ PINS_VECTOR1, "Saturation" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_INPUT = 0,
		ID_SATURATION,
	};

	DECLARE_NODE_CLASS(Saturation)

}; // Saturation

}
}