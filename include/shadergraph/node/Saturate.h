#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Saturate : public Node
{
public:
	Saturate()
		: Node("Saturate", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Saturate

}
}