#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Exponential : public Node
{
public:
	enum BaseType
	{
		BASE_E = 0,
		BASE_2,
	};

public:
	Exponential()
		: Node("Exponential", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	BaseType GetType() const { return m_type; }
	void SetType(BaseType type) { m_type = type; }

private:
	BaseType m_type = BASE_E;

	DECLARE_NODE_CLASS(Exponential)

}; // Exponential

}
}