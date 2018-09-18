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
			{ PINS_VECTOR1, "A" },
			{ PINS_VECTOR1, "B" },
			{ PINS_VECTOR1, "T" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

public:
	enum InputId
	{
		ID_A = 0,
		ID_B,
		ID_T
	};

	DECLARE_NODE_CLASS(InverseLerp)

}; // InverseLerp

}
}