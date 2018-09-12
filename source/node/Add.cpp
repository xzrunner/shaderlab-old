#include "shadergraph/node/Add.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

const std::string Add::TYPE_NAME = "sg_add";

Add::Add()
	: bp::Node("Add")
{
	AddPins(m_input0 = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "A", *this));
	AddPins(m_input1 = std::make_shared<Pins>(true, 1, PINS_VECTOR1, "B", *this));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();
}

}
}