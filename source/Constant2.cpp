#include "shadergraph/Constant2.h"
#include "shadergraph/PinsType.h"

#include <cpputil/StringHelper.h>
#include <blueprint/Pins.h>

namespace shadergraph
{

const std::string Constant2::TYPE_NAME = "mat_constant2";

Constant2::Constant2()
	: Node("Constant2")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, PINS_VECTOR2, "", *this));

	Layout();

	UpdateTitle();
}

sm::vec3 Constant2::ToVec3() const
{
	return sm::vec3(m_val.x, m_val.y, 0);
}

void Constant2::SetValue(const sm::vec2& val)
{
	m_val = val;
	UpdateTitle();
}

void Constant2::UpdateTitle()
{
	m_style.small_title = true;
	m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.y, 2);
}

}