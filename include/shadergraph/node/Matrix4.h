#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Matrix4 : public Node
{
public:
	Matrix4()
		: Node("Matrix4", false)
	{
		InitPins({
		},{
			{ PINS_MATRIX4, "Out" }
		});
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::mat4& val) { m_val = val; }

private:
	sm::mat4 m_val;

	RTTR_ENABLE(Node)

}; // Matrix4

}
}