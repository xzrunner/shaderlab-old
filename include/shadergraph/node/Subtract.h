#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Subtract : public Node
{
public:
	Subtract()
		: Node("Subtract", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Subtract

}
}