#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class GradientNoise : public Node
{
public:
	GradientNoise()
		: Node("GradientNoise", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Scale" },
		},{
			{ PINS_VECTOR1, "Out", }
		}, true);
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_SCALE,
	};

	DECLARE_NODE_CLASS(GradientNoise)

}; // GradientNoise

}
}