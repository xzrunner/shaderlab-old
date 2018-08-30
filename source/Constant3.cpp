#include "ematerial/Constant3.h"

#include <blueprint/Pins.h>

namespace ematerial
{

Constant3::Constant3()
	: Node("Constant3")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "", *this));

	Layout();
}

}