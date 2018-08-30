#include "ematerial/Constant2.h"

#include <blueprint/Pins.h>

namespace ematerial
{

Constant2::Constant2()
	: Node("Constant2")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "", *this));

	Layout();
}

}