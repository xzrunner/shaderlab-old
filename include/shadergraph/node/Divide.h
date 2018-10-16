#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Divide : public Node
{
public:
	Divide()
		: Node("Divide", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Divide

}
}