#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class HyperbolicTangent : public Node
{
public:
	HyperbolicTangent()
		: Node("HyperbolicTangent", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	DECLARE_NODE_CLASS(HyperbolicTangent)

}; // HyperbolicTangent

}
}