#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Posterize : public Node
{
public:
	Posterize()
		: Node("Posterize", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
			{ PINS_DYNAMIC_VECTOR, "Steps" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	enum InputID
	{
		ID_INPUT = 0,
		ID_STEPS,
	};

	DECLARE_NODE_CLASS(Posterize)

}; // Posterize

}
}