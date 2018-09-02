#include "shadergraph/Constant1.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace shadergraph
{

const std::string Constant1::TYPE_NAME = "mat_constant1";

Constant1::Constant1()
	: Node("Constant1")
{
	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();

	UpdateTitle();
}

sm::vec3 Constant1::ToVec3() const
{
	return sm::vec3(m_val, m_val, m_val);
}

void Constant1::SetValue(float val)
{
	m_val = val;
	UpdateTitle();
}

void Constant1::UpdateTitle()
{
	m_style.small_title = true;
	m_title = cpputil::StringHelper::ToString(m_val, 2);
}

}