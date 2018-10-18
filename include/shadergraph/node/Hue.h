#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class Hue : public Node
{
public:
	Hue()
		: Node("Hue", true)
	{
		InitPins({
			{ PINS_VECTOR3, "In" },
			{ PINS_VECTOR1, "Offset" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

	auto GetAngleType() const { return m_type; }
	void SetAngleType(PropAngleType type) { m_type = type; }

public:
	enum InputID
	{
		ID_INPUT = 0,
		ID_OFFSET,
	};

private:
	PropAngleType m_type = PropAngleType::RADIAN;

	RTTR_ENABLE(Node)

}; // Hue

}
}