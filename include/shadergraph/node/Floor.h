#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Floor : public Node
{
public:
	Floor()
		: Node("Floor", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Floor

}
}