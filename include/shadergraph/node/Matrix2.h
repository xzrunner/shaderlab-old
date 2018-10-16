#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Matrix2 : public Node
{
public:
	Matrix2()
		: Node("Matrix2", false)
	{
		InitPins({
		},{
			{ PINS_MATRIX2, "Out" }
		});
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::mat2& val) { m_val = val; }

private:
	sm::mat2 m_val;

	RTTR_ENABLE(Node)

}; // Matrix2

}
}