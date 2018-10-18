#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class Comparison : public Node
{
public:
	Comparison()
		: Node("Comparison", false, true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_BOOLEAN, "Out", }
		});
	}

	auto GetType() const { return m_type; }
	void SetType(CmpType type) { m_type = type; }

	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

private:
	CmpType m_type = CmpType::EQUAL;

	RTTR_ENABLE(Node)

}; // Comparison

}
}