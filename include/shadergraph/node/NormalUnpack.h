#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class NormalUnpack : public Node
{
public:
	NormalUnpack()
		: Node("NormalUnpack", true)
	{
		InitPins({
			{ PINS_VECTOR4, "In" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // NormalUnpack

}
}