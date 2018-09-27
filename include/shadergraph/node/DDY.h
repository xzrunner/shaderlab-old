#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class DDY : public Node
{
public:
	DDY()
		: Node("DDY", false)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	DECLARE_NODE_CLASS(DDY)

}; // DDY

}
}