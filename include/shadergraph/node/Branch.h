#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Branch : public Node
{
public:
	Branch()
		: Node("Branch", false, true)
	{
		InitPins({
			{ PINS_BOOLEAN,        "Predicate" },
			{ PINS_DYNAMIC_VECTOR, "True" },
			{ PINS_DYNAMIC_VECTOR, "False" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	enum InputID
	{
		ID_PREDICATE = 0,
		ID_TRUE,
		ID_FALSE,
	};

	DECLARE_NODE_CLASS(Branch)

}; // Branch

}
}