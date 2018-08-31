#include "ematerial/Add.h"
#include "ematerial/Utility.h"

#include <blueprint/Pins.h>

namespace ematerial
{

Add::Add()
	: Node("Add")
{
	AddPins(m_input0 = std::make_shared<bp::node::Pins>(
		true, 0, bp::node::PINS_VECTOR, "", *this));
	AddPins(m_input1 = std::make_shared<bp::node::Pins>(
		true, 1, bp::node::PINS_VECTOR, "", *this));

	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "", *this));

	Layout();
}

sm::vec3 Add::ToVec3() const
{
	sm::vec3 add0, add1;
	if (m_input0) {
		add0 = Utility::CalcNodeInputVal(*m_input0);
	}
	if (m_input1) {
		add1 = Utility::CalcNodeInputVal(*m_input1);
	}
	return add0 + add1;
}

}