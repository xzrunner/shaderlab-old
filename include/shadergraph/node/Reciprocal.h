#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Reciprocal : public Node
{
public:
	Reciprocal()
		: Node("Reciprocal", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	DECLARE_NODE_CLASS(Reciprocal)

}; // Reciprocal

}
}