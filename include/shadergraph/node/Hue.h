#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

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

	bool IsRadians() const { return m_is_radians; }
	void SetRadians(bool rad) { m_is_radians = rad; }

public:
	enum InputID
	{
		ID_INPUT = 0,
		ID_OFFSET,
	};

private:
	bool m_is_radians = true;

	RTTR_ENABLE(Node)

}; // Hue

}
}