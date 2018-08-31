#include "ematerial/Divide.h"
#include "ematerial/Utility.h"

#include <blueprint/Pins.h>

namespace ematerial
{

Divide::Divide()
	: Node("Divide")
{
	AddPins(m_input0 = std::make_shared<bp::node::Pins>(
		true, 0, bp::node::PINS_VECTOR, "", *this));
	AddPins(m_input1 = std::make_shared<bp::node::Pins>(
		true, 1, bp::node::PINS_VECTOR, "", *this));

	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "", *this));

	Layout();
}

sm::vec3 Divide::ToVec3() const
{
	sm::vec3 d0, d1;
	if (m_input0) {
		d0 = Utility::CalcNodeInputVal(*m_input0);
	}
	if (m_input1) {
		d1 = Utility::CalcNodeInputVal(*m_input1);
	} else {
		d1.Set(1, 1, 1);
	}

	sm::vec3 ret;
	auto ep = std::numeric_limits<float>::epsilon();
	if (fabs(d1.x) > ep) {
		ret.x = d0.x / d1.x;
	}
	if (fabs(d1.y) > ep) {
		ret.y = d0.y / d1.y;
	}
	if (fabs(d1.z) > ep) {
		ret.z = d0.z / d1.z;
	}
	return ret;
}

}