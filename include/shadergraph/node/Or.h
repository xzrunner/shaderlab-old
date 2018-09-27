#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Or : public Node
{
public:
	Or()
		: Node("Or", false)
	{
		InitPins({
			{ PINS_BOOLEAN, "A" },
			{ PINS_BOOLEAN, "B" },
		},{
			{ PINS_BOOLEAN, "Out", }
		});
	}

	DECLARE_NODE_CLASS(Or)

}; // Or

}
}