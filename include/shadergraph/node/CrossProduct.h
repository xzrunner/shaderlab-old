#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class CrossProduct : public Node
{
public:
	CrossProduct()
		: Node("CrossProduct", true)
	{
		InitPins({
			{ PINS_VECTOR3, "A" },
			{ PINS_VECTOR3, "B" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

	RTTR_ENABLE(Node)

}; // CrossProduct

}
}