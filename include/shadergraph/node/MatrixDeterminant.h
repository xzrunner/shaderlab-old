#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class MatrixDeterminant : public Node
{
public:
	MatrixDeterminant()
		: Node("MatrixDeterminant", false)
	{
		InitPins({
			{ PINS_DYNAMIC_MATRIX, "In" },
		},{
			{ PINS_VECTOR1, "Out" },
		});
	}

	RTTR_ENABLE(Node)

}; // MatrixDeterminant

}
}