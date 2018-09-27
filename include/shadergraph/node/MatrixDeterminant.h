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

	DECLARE_NODE_CLASS(MatrixDeterminant)

}; // MatrixDeterminant

}
}