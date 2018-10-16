#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Not : public Node
{
public:
	Not()
		: Node("Not", false)
	{
		InitPins({
			{ PINS_BOOLEAN, "In" },
		},{
			{ PINS_BOOLEAN, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Not

}
}