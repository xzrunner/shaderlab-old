#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ColorAddMul : public Node
{
public:
	ColorAddMul()
		: Node("ColorAddMul", true)
	{
		InitPins({
			{ PINS_COLOR, "In" },
			{ PINS_COLOR, "Mul" },
			{ PINS_COLOR, "Add" },
		},{
			{ PINS_COLOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_COL = 0,
		ID_MUL,
		ID_ADD,
	};

	RTTR_ENABLE(Node)

}; // ColorAddMul

}
}