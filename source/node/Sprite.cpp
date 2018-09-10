#include "shadergraph/node/Sprite.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

const std::string Sprite::TYPE_NAME = "sg_sprite";

Sprite::Sprite()
	: Node("Sprite")
{
	AddPins(m_tex     = std::make_shared<Pins>(true, ID_TEX,     PINS_TEXTURE2D, "Tex", *this));
	AddPins(m_col_mul = std::make_shared<Pins>(true, ID_COL_MUL, PINS_VECTOR3,   "Mul", *this));
	AddPins(m_col_add = std::make_shared<Pins>(true, ID_COL_ADD, PINS_VECTOR3,   "Add", *this));

	Layout();
}

}
}