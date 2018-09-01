#include "ematerial/Multiply.h"
#include "ematerial/Utility.h"

#include <blueprint/Pins.h>

namespace ematerial
{

const std::string Multiply::TYPE_NAME = "mat_mul";

Multiply::Multiply()
	: Node("Multiply")
{
	AddPins(m_input0 = std::make_shared<bp::node::Pins>(
		true, 0, bp::node::PINS_VECTOR, "", *this));
	AddPins(m_input1 = std::make_shared<bp::node::Pins>(
		true, 1, bp::node::PINS_VECTOR, "", *this));

	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "", *this));

	Layout();
}

sm::vec3 Multiply::ToVec3() const
{
	sm::vec3 mul0, mul1;
	if (m_input0) {
		mul0 = Utility::CalcNodeInputVal(*m_input0);
	}
	if (m_input1) {
		mul1 = Utility::CalcNodeInputVal(*m_input1);
	}

	sm::vec3 ret;
	ret.x = mul0.x * mul1.x;
	ret.y = mul0.y * mul1.y;
	ret.z = mul0.z * mul1.z;
	return ret;
}

}