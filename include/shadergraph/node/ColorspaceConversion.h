#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ColorspaceConversion : public Node
{
public:
	enum ColorType
	{
		COL_RGB,
		COL_LINEAR,
		COL_HSV,
	};

public:
	ColorspaceConversion()
		: Node("ColorspaceConversion", true)
	{
		InitPins({
			{ PINS_COLOR, "In" },
		},{
			{ PINS_COLOR, "Out", }
		});
	}

	ColorType GetFromType() const { return m_from; }
	void SetFromType(ColorType t) { m_from = t; }
	ColorType GetToType() const { return m_to; }
	void SetToType(ColorType t) { m_to = t; }

private:
	ColorType m_from = COL_RGB, m_to = COL_RGB;

	RTTR_ENABLE(Node)

}; // ColorspaceConversion

}
}