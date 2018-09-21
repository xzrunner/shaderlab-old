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
			{ PINS_COLOR, "In" },
		},{
			{ PINS_COLOR, "Out", }
		});
	}

	DECLARE_NODE_CLASS(Gray)

}; // Gray

}
}