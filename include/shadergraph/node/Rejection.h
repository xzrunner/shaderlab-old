#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Rejection : public Node
{
public:
	Rejection()
		: Node("Rejection", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

	RTTR_ENABLE(Node)

}; // Rejection

}
}