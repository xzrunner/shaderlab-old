#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class TilingAndOffset : public Node
{
public:
	TilingAndOffset()
		: Node("TilingAndOffset", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR2, "Tilling" },
			{ PINS_VECTOR2, "Offset" },
		},{
			{ PINS_VECTOR2, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_UV = 0,
		ID_TILLING,
		ID_OFFSET,
	};

	DECLARE_NODE_CLASS(TilingAndOffset)

}; // TilingAndOffset

}
}