#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Step : public Node
{
public:
	Step()
		: Node("Step", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
			{ PINS_DYNAMIC_VECTOR, "Edge" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	enum InputID
	{
		ID_INPUT = 0,
		ID_EDGE,
	};

	DECLARE_NODE_CLASS(Step)

}; // Step

}
}