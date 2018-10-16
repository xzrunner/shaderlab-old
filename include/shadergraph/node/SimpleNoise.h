#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class SimpleNoise : public Node
{
public:
	SimpleNoise()
		: Node("SimpleNoise", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Scale" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_SCALE,
	};

	RTTR_ENABLE(Node)

}; // SimpleNoise

}
}