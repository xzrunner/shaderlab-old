#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Split : public Node
{
public:
	Split()
		: Node("Split", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_VECTOR1, "R" },
			{ PINS_VECTOR1, "G" },
			{ PINS_VECTOR1, "B" },
			{ PINS_VECTOR1, "A" },
		});
	}

public:
	enum OutputID
	{
		ID_R = 0,
		ID_G,
		ID_B,
		ID_A,
	};

	DECLARE_NODE_CLASS(Split)

}; // Split

}
}