#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

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

	bool IsRadians() const { return m_is_radians; }
	void SetRadians(bool rad) { m_is_radians = rad; }

public:
	enum InputID
	{
		ID_UV = 0,
		ID_CENTER,
		ID_ROTATION,
	};

private:
	bool m_is_radians = true;

	RTTR_ENABLE(Node)

}; // Rotate

}
}