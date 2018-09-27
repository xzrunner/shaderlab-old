#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class DDX : public Node
{
public:
	DDX()
		: Node("DDX", false)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	DECLARE_NODE_CLASS(DDX)

}; // DDX

}
}