#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Distance : public Node
{
public:
	Distance()
		: Node("Distance", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

	DECLARE_NODE_CLASS(Distance)

}; // Distance

}
}