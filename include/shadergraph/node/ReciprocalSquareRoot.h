#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ReciprocalSquareRoot : public Node
{
public:
	ReciprocalSquareRoot()
		: Node("ReciprocalSquareRoot", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	RTTR_ENABLE(Node)

}; // ReciprocalSquareRoot

}
}