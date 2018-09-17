#include "shadergraph/node/Remap.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

const std::string Remap::TYPE_NAME = "sg_remap";

Remap::Remap()
	: Node("Remap", true)
{
	AddPins(m_in   = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "In",   *this));
	AddPins(m_from = std::make_shared<Pins>(true, 1, PINS_VECTOR2, "From", *this));
	AddPins(m_to   = std::make_shared<Pins>(true, 2, PINS_VECTOR2, "To",   *this));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	m_from->SetTypeStatic(true);
	m_to->SetTypeStatic(true);

	Layout();
}

}
}