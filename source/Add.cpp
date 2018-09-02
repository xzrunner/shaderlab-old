#include "shadergraph/Add.h"
#include "shadergraph/Utility.h"
#include "shadergraph/Pins.h"

namespace shadergraph
{

const std::string Add::TYPE_NAME = "mat_add";

Add::Add()
	: Node("Add")
{
	AddPins(m_input0 = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "A", *this, true));
	AddPins(m_input1 = std::make_shared<Pins>(true, 1, PINS_VECTOR1, "B", *this, true));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this, true));

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