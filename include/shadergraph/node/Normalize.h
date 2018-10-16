#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Normalize : public Node
{
public:
	Normalize()
		: Node("Normalize", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	RTTR_ENABLE(Node)

}; // Normalize

}
}