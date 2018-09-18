#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Add : public Node
{
public:
	Add()
		: Node("Add", true)
	{
		InitPins({
			{ PINS_VECTOR1, "A" },
			{ PINS_VECTOR1, "B" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

	DECLARE_NODE_CLASS(Add)

}; // Add

}
}