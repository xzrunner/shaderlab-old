#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class RandomRange : public Node
{
public:
	RandomRange()
		: Node("RandomRange", true)
	{
		InitPins({
			{ PINS_VECTOR2, "Seed" },
			{ PINS_DYNAMIC_VECTOR, "Min" },
			{ PINS_DYNAMIC_VECTOR, "Max" },
			},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_SEED = 0,
		ID_MIN,
		ID_MAX
	};

	RTTR_ENABLE(Node)

}; // RandomRange

}
}