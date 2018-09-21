#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ColorMap : public Node
{
public:
	ColorMap()
		: Node("ColorMap", true)
	{
		InitPins({
			{ PINS_COLOR, "Col" },
			{ PINS_COLOR, "MapR" },
			{ PINS_COLOR, "MapG" },
			{ PINS_COLOR, "MapB" },
		},{
			{ PINS_COLOR, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_COL = 0,
		ID_RMAP,
		ID_GMAP,
		ID_BMAP,
	};

	DECLARE_NODE_CLASS(ColorMap)

}; // ColorMap

}
}