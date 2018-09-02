#include "shadergraph/TextureSample.h"

#include <blueprint/Pins.h>

namespace shadergraph
{

const std::string TextureSample::TYPE_NAME = "mat_tex_sample";

TextureSample::TextureSample()
	: Node("TextureSample")
{
	AddPins(m_tex = std::make_shared<bp::node::Pins>(
		true, 0, bp::node::PINS_OBJECT, "tex", *this));
	AddPins(m_uv = std::make_shared<bp::node::Pins>(
		true, 1, bp::node::PINS_VECTOR, "uv", *this));

	AddPins(m_rgba = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_VECTOR, "rgba", *this));
	AddPins(m_r = std::make_shared<bp::node::Pins>(
		false, 1, bp::node::PINS_FLOAT, "r", *this));
	AddPins(m_g = std::make_shared<bp::node::Pins>(
		false, 2, bp::node::PINS_FLOAT, "g", *this));
	AddPins(m_b = std::make_shared<bp::node::Pins>(
		false, 3, bp::node::PINS_FLOAT, "b", *this));
	AddPins(m_a = std::make_shared<bp::node::Pins>(
		false, 4, bp::node::PINS_FLOAT, "a", *this));

	Layout();
}

}