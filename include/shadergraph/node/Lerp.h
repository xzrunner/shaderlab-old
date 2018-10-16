#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Lerp : public Node
{
public:
	Lerp()
		: Node("Lerp", true)
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

	RTTR_ENABLE(Node)

}; // Lerp

}
}