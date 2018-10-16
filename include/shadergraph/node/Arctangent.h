#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Arctangent : public Node
{
public:
	Arctangent()
		: Node("Arctangent", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Arctangent

}
}