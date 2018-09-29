#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Contrast : public Node
{
public:
	Contrast()
		: Node("Contrast", true)
	{
		InitPins({
			{ PINS_VECTOR3, "In" },
			{ PINS_VECTOR1, "Contrast" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_INPUT = 0,
		ID_CONTRAST,
	};

	DECLARE_NODE_CLASS(Contrast)

}; // Contrast

}
}