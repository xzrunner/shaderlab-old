#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class InverseLerp : public Node
{
public:
	InverseLerp()
		: Node("InverseLerp", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
			{ PINS_DYNAMIC_VECTOR, "T" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_A = 0,
		ID_B,
		ID_T
	};

	DECLARE_NODE_CLASS(InverseLerp)

}; // InverseLerp

}
}