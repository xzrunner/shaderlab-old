#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class HyperbolicCosine : public Node
{
public:
	HyperbolicCosine()
		: Node("HyperbolicCosine", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	DECLARE_NODE_CLASS(HyperbolicCosine)

}; // HyperbolicCosine

}
}