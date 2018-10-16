#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class UV : public Node
{
public:
	UV()
		: Node("UV", false)
	{
		// todo channel
		SetName("v_texcoord");

		InitPins({
		},{
			{ PINS_VECTOR2, "Out", }
		});
	}

	RTTR_ENABLE(Node)

}; // UV

}
}