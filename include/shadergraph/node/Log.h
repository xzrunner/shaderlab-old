#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Log : public Node
{
public:
	enum BaseType
	{
		BASE_E = 0,
		BASE_2,
		BASE_10,
	};

public:
	Log()
		: Node("Log", true)
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

	RTTR_ENABLE(Node)

}; // Log

}
}