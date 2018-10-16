#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Remap : public Node
{
public:
	Remap()
		: Node("Remap", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
			{ PINS_VECTOR2, "From" },
			{ PINS_VECTOR2, "To" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_IN = 0,
		ID_FROM,
		ID_TO
	};

	RTTR_ENABLE(Node)

}; // Remap

}
}