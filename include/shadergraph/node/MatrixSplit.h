#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class MatrixSplit : public Node
{
public:
	MatrixSplit()
		: Node("MatrixSplit", false)
	{
		InitPins({
			{ PINS_DYNAMIC_MATRIX, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "M0" },
			{ PINS_DYNAMIC_VECTOR, "M1" },
			{ PINS_DYNAMIC_VECTOR, "M2" },
			{ PINS_DYNAMIC_VECTOR, "M3" },
		});
	}

	void SetType(MatrixType type) { m_type = type; }
	MatrixType GetType() const { return m_type; }

	enum OutputID
	{
		ID_M0 = 0,
		ID_M1,
		ID_M2,
		ID_M3,
	};

private:
	MatrixType m_type = MatrixType::ROW;

	RTTR_ENABLE(Node)

}; // MatrixSplit

}
}