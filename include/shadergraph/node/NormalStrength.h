#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class NormalStrength : public Node
{
public:
	NormalStrength()
		: Node("NormalStrength", true)
	{
		InitPins({
			{ PINS_VECTOR3, "In" },
			{ PINS_VECTOR1, "Strength" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

	enum InputID
	{
		ID_INPUT = 0,
		ID_STRENGTH,
	};

	RTTR_ENABLE(Node)

}; // NormalStrength

}
}