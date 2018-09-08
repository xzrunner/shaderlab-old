#include "shadergraph/node/TextureSample.h"
#include "shadergraph/Pins.h"

namespace shadergraph
{
namespace node
{

const std::string TextureSample::TYPE_NAME = "sg_tex_sample";

TextureSample::TextureSample()
	: Node("TextureSample")
{
	AddPins(m_tex = std::make_shared<Pins>(true, 0, PINS_TEXTURE2D, "Tex", *this));
	AddPins(m_uv  = std::make_shared<Pins>(true, 1, PINS_VECTOR2, "UV", *this));

	AddPins(m_rgba = std::make_shared<Pins>(false, 0, PINS_VECTOR4, "RGBA", *this));
	AddPins(m_r    = std::make_shared<Pins>(false, 1, PINS_VECTOR1, "R", *this));
	AddPins(m_g    = std::make_shared<Pins>(false, 2, PINS_VECTOR1, "G", *this));
	AddPins(m_b    = std::make_shared<Pins>(false, 3, PINS_VECTOR1, "B", *this));
	AddPins(m_a    = std::make_shared<Pins>(false, 4, PINS_VECTOR1, "A", *this));

	Layout();
}

}
}