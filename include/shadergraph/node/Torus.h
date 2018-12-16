#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Torus : public Node
{
public:
	Torus()
		: Node("Torus", true)
	{
		InitPins({
			{ PINS_VECTOR3, "Pos" },
			{ PINS_VECTOR2, "Radius" },
		},{
			{ PINS_VECTOR1, "Dis", },
		});
	}

public:
	enum InputID
	{
		ID_POS = 0,
		ID_RADIUS,
	};

	RTTR_ENABLE(Node)

}; // Torus

}
}