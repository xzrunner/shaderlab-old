#include "shadergraph/Constant4.h"

#include <blueprint/Pins.h>
#include <cpputil/StringHelper.h>

namespace shadergraph
{

const std::string Constant4::TYPE_NAME = "mat_constant4";

Constant4::Constant4()
	: Node("Constant4")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "", *this));

	Layout();

	UpdateTitle();
}

sm::vec3 Constant4::ToVec3() const
{
	return sm::vec3(m_val.x, m_val.y, m_val.z);
}

void Constant4::SetValue(const sm::vec4& val)
{
	m_val = val;
	UpdateTitle();
}

void Constant4::UpdateTitle()
{
	m_style.small_title = true;
	m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.y, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.z, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.w, 2);
}

}