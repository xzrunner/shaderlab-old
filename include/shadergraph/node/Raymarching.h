#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Raymarching : public Node
{
public:
	Raymarching()
		: Node("Raymarching", true)
	{
		InitPins({
			{ PINS_VECTOR2,  "UV" },
			{ PINS_FUNCTION, "SDF" },
		},{
			{ PINS_VECTOR4,  "Out", }
		});
	}

	enum InputID
	{
		ID_UV = 0,
		ID_SDF,
	};

	RTTR_ENABLE(Node)

}; // Raymarching

}
}