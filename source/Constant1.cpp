#include "ematerial/Constant1.h"

#include <blueprint/Pins.h>

namespace ematerial
{

Constant1::Constant1()
	: Node("Constant1")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_FLOAT, "", *this));

	Layout();
}

}