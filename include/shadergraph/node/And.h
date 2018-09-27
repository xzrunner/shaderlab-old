#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class And : public Node
{
public:
	And()
		: Node("And", false, true)
	{
		InitPins({
			{ PINS_BOOLEAN, "A" },
			{ PINS_BOOLEAN, "B" },
		},{
			{ PINS_BOOLEAN, "Out", }
		});
	}

	DECLARE_NODE_CLASS(And)

}; // And

}
}