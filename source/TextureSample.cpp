#include "shadergraph/TextureSample.h"
#include "shadergraph/PinsType.h"

#include <blueprint/Pins.h>

namespace shadergraph
{

const std::string TextureSample::TYPE_NAME = "mat_tex_sample";

TextureSample::TextureSample()
	: Node("TextureSample")
{
	AddPins(m_tex = std::make_shared<bp::node::Pins>(
		true, 0, PINS_TEXTURE2D, "tex", *this));
	AddPins(m_uv = std::make_shared<bp::node::Pins>(
		true, 1, PINS_VECTOR2, "uv", *this));

	AddPins(m_rgba = std::make_shared<bp::node::Pins>(
		false, 0, PINS_VECTOR4, "rgba", *this));
	AddPins(m_r = std::make_shared<bp::node::Pins>(
		false, 1, PINS_VECTOR1, "r", *this));
	AddPins(m_g = std::make_shared<bp::node::Pins>(
		false, 2, PINS_VECTOR1, "g", *this));
	AddPins(m_b = std::make_shared<bp::node::Pins>(
		false, 3, PINS_VECTOR1, "b", *this));
	AddPins(m_a = std::make_shared<bp::node::Pins>(
		false, 4, PINS_VECTOR1, "a", *this));

	Layout();
}

}