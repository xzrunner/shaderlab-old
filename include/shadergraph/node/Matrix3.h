#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Matrix3 : public Node
{
public:
	Matrix3()
		: Node("Matrix3", false)
	{
		InitPins({
		},{
			{ PINS_MATRIX3, "Out" }
		});
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::mat3& val) { m_val = val; }

private:
	sm::mat3 m_val;

	RTTR_ENABLE(Node)

}; // Matrix3

}
}