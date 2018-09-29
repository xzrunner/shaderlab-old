#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class WhiteBalance : public Node
{
public:
	WhiteBalance()
		: Node("WhiteBalance", true)
	{
		InitPins({
			{ PINS_VECTOR3, "In" },
			{ PINS_VECTOR1, "Temperature" },
			{ PINS_VECTOR1, "Tint" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_INPUT = 0,
		ID_TEMPERATURE,
		ID_TINT,
	};

	DECLARE_NODE_CLASS(WhiteBalance)

}; // WhiteBalance

}
}