#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Twirl : public Node
{
public:
	Twirl()
		: Node("Twirl", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR2, "Center" },
			{ PINS_VECTOR1, "Strength" },
			{ PINS_VECTOR2, "Offset" },
		},{
			{ PINS_VECTOR2, "Out", }
		}, true);
	}

public:
	enum InputId
	{
		ID_UV = 0,
		ID_CENTER,
		ID_STRENGTH,
		ID_OFFSET,
	};

	DECLARE_NODE_CLASS(Twirl)

}; // Twirl

}
}