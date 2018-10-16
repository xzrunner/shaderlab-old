#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class NormalCreate : public Node
{
public:
	NormalCreate()
		: Node("NormalCreate", true)
	{
		InitPins({
			{ PINS_TEXTURE2D, "Tex" },
			{ PINS_VECTOR2,   "UV" },
			{ PINS_VECTOR1,   "Offset" },
			{ PINS_VECTOR1,   "Strength" },
		},{
			{ PINS_VECTOR3,   "Out", }
		});
	}

	enum InputID
	{
		ID_TEX = 0,
		ID_UV,
		ID_OFFSET,
		ID_STRENGTH,
	};

	RTTR_ENABLE(Node)

}; // NormalCreate

}
}