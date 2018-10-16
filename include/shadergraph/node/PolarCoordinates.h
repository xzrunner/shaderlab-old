#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class PolarCoordinates : public Node
{
public:
	PolarCoordinates()
		: Node("PolarCoordinates", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR2, "Center" },
			{ PINS_VECTOR1, "Radial Scale" },
			{ PINS_VECTOR1, "Length Scale" },
		},{
			{ PINS_VECTOR2, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_CENTER,
		ID_RADIAL_SCALE,
		ID_LENGTH_SCALE,
	};

	RTTR_ENABLE(Node)

}; // PolarCoordinates

}
}