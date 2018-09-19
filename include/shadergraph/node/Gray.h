#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Gray : public Node
{
public:
	Gray()
		: Node("Gray", true)
	{
		InitPins({
			{ PINS_VECTOR4, "In" },
		},{
			{ PINS_VECTOR4, "Out", }
		});
	}

	DECLARE_NODE_CLASS(Gray)

}; // Gray

}
}