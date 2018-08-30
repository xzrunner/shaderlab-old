#include "ematerial/Constant4.h"

#include <blueprint/Pins.h>

namespace ematerial
{

Constant4::Constant4()
	: Node("Constant4")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_FLOAT, "", *this));

	Layout();
}

}