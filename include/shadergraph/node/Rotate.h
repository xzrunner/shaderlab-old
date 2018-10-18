#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class Rotate : public Node
{
public:
	Rotate()
		: Node("Rotate", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR2, "Center" },
			{ PINS_VECTOR1, "Rotation" },
		},{
			{ PINS_VECTOR2, "Out", }
		});
	}

	auto GetAngleType() const { return m_type; }
	void SetAngleType(PropAngleType type) { m_type = type; }

public:
	enum InputID
	{
		ID_UV = 0,
		ID_CENTER,
		ID_ROTATION,
	};

private:
	PropAngleType m_type = PropAngleType::RADIAN;

	RTTR_ENABLE(Node)

}; // Rotate

}
}