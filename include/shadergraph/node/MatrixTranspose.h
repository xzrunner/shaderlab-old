#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class MatrixTranspose : public Node
{
public:
	MatrixTranspose()
		: Node("MatrixTranspose", false)
	{
		InitPins({
			{ PINS_DYNAMIC_MATRIX, "In" },
		},{
			{ PINS_DYNAMIC_MATRIX, "Out" },
		});
	}

	RTTR_ENABLE(Node)

}; // MatrixTranspose

}
}