#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Minimum : public Node
{
public:
	Minimum()
		: Node("Minimum", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

	DECLARE_NODE_CLASS(Minimum)

}; // Minimum

}
}