#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Multiply : public Node
{
public:
	Multiply()
		: Node("Multiply", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Multiply

}
}