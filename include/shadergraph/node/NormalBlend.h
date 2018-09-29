#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class NormalBlend : public Node
{
public:
	NormalBlend()
		: Node("NormalBlend", true)
	{
		InitPins({
			{ PINS_VECTOR3, "A" },
			{ PINS_VECTOR3, "B" },
		},{
			{ PINS_VECTOR3, "Out", }
		});
	}

	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

	DECLARE_NODE_CLASS(NormalBlend)

}; // NormalBlend

}
}