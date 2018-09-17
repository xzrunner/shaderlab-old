#include "shadergraph/node/UV.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

const std::string UV::TYPE_NAME = "sg_uv";

UV::UV()
	: bp::Node("UV")
{
	// todo channel
	SetName("v_texcoord");

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR2, "Out", *this));

	Layout();
}

}
}