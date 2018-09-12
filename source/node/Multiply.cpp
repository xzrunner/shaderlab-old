#include "shadergraph/node/Multiply.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

const std::string Multiply::TYPE_NAME = "sg_mul";

Multiply::Multiply()
	: bp::Node("Multiply")
{
	AddPins(m_input0 = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "A", *this));
	AddPins(m_input1 = std::make_shared<Pins>(true, 1, PINS_VECTOR1, "B", *this));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();
}

}
}