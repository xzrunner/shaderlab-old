#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Voronoi : public Node
{
public:
	Voronoi()
		: Node("Voronoi", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Angle Offset" },
			{ PINS_VECTOR1, "Cell Density" },
		},{
			{ PINS_VECTOR1, "Out", },
			{ PINS_VECTOR1, "Cells", },
		});
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_ANGLE_OFFSET,
		ID_CELL_DENSITY,
	};

	enum OutputID
	{
		ID_OUT,
		ID_CELLS,
	};

	RTTR_ENABLE(Node)

}; // Voronoi

}
}