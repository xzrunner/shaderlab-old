#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Length : public Node
{
public:
	Length()
		: Node("Length", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // Length

}
}