#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class MatrixConstruction : public Node
{
public:
	MatrixConstruction()
		: Node("MatrixConstruction", false)
	{
		InitPins({
			{ PINS_VECTOR4, "M0" },
			{ PINS_VECTOR4, "M1" },
			{ PINS_VECTOR4, "M2" },
			{ PINS_VECTOR4, "M3" },
		},{
			{ PINS_MATRIX4, "Mat4" },
			{ PINS_MATRIX3, "Mat3" },
			{ PINS_MATRIX2, "Mat2" },
		});
	}

	void SetType(MatrixType type) { m_type = type; }
	MatrixType GetType() const { return m_type; }

	enum InputID
	{
		ID_M0 = 0,
		ID_M1,
		ID_M2,
		ID_M3,
	};

	enum OutputID
	{
		ID_MAT4,
		ID_MAT3,
		ID_MAT2,
	};

private:
	MatrixType m_type = MatrixType::ROW;

	RTTR_ENABLE(Node)

}; // MatrixConstruction

}
}