#include "shadergraph/node/InverseLerp.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

const std::string InverseLerp::TYPE_NAME = "sg_inverse_lerp";

InverseLerp::InverseLerp()
	: Node("InverseLerp", true)
{
	AddPins(m_a = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "A", *this));
	AddPins(m_b = std::make_shared<Pins>(true, 1, PINS_VECTOR1, "B", *this));
	AddPins(m_t = std::make_shared<Pins>(true, 2, PINS_VECTOR1, "T", *this));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();
}

}
}