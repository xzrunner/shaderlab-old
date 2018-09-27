#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Clamp : public Node
{
public:
	Clamp()
		: Node("Clamp", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
			{ PINS_DYNAMIC_VECTOR, "Min" },
			{ PINS_DYNAMIC_VECTOR, "Max" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_IN = 0,
		ID_MIN,
		ID_MAX
	};

	DECLARE_NODE_CLASS(Clamp)

}; // Clamp

}
}