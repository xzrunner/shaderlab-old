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

		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR2, "Out", *this));

		Layout();
	}

	DECLARE_NODE_CLASS(UV)

}; // UV

}
}