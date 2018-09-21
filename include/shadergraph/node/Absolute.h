#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Absolute : public Node
{
public:
	Absolute()
		: Node("Absolute", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	DECLARE_NODE_CLASS(Absolute)

}; // Absolute

}
}