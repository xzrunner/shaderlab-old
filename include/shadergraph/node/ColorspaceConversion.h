#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class ColorspaceConversion : public Node
{
public:
	ColorspaceConversion()
		: Node("ColorspaceConversion", true)
		, m_type(ColorType::RGB, ColorType::RGB)
	{
		InitPins({
			{ PINS_COLOR, "In" },
		},{
			{ PINS_COLOR, "Out", }
		});
	}

	auto& GetType() const { return m_type; }
	void SetType(const PropColorTrans& type) { m_type = type; }

private:
	PropColorTrans m_type;

	RTTR_ENABLE(Node)

}; // ColorspaceConversion

}
}