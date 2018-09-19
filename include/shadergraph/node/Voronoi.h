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

		for (auto& p : GetAllInput()) {
			p->SetTypeStatic(true);
		}
		for (auto& p : GetAllOutput()) {
			p->SetTypeStatic(true);
		}
	}

public:
	enum InputId
	{
		ID_UV = 0,
		ID_ANGLE_OFFSET,
		ID_CELL_DENSITY,
	};

	enum OutputId
	{
		ID_OUT,
		ID_CELLS,
	};

	DECLARE_NODE_CLASS(Voronoi)

}; // Voronoi

}
}