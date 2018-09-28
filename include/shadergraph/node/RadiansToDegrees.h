#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class RadiansToDegrees : public Node
{
public:
	RadiansToDegrees()
		: Node("RadiansToDegrees", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	DECLARE_NODE_CLASS(RadiansToDegrees)

}; // RadiansToDegrees

}
}