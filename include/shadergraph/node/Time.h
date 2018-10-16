#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Time : public Node
{
public:
	Time()
		: Node("Time", false)
	{
		InitPins({
		},{
			{ PINS_VECTOR1, "Time", },
			{ PINS_VECTOR1, "Sine Time", },
			{ PINS_VECTOR1, "Cosine Time", },
			{ PINS_VECTOR1, "Delta Time", },
			{ PINS_VECTOR1, "Smooth Delta", },
		});
	}

public:
	enum InputID
	{
		ID_TIME = 0,
		ID_SINE_TIME,
		ID_COSINE_TIME,
		ID_DELTA_TIME,
		ID_SMOOTH_DELTA,
	};

	RTTR_ENABLE(Node)

}; // Time

}
}