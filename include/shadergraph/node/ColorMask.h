#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ColorMask : public Node
{
public:
	ColorMask()
		: Node("ColorMask", true)
	{
		InitPins({
			{ PINS_COLOR,   "In" },
			{ PINS_COLOR,   "Mask" },
			{ PINS_VECTOR1, "Range" },
			{ PINS_VECTOR1, "Fuzziness" },
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

public:
	enum InputID
	{
		ID_COL = 0,
		ID_MASK,
		ID_RANGE,
		ID_FUZZINESS,
	};

	DECLARE_NODE_CLASS(ColorMask)

}; // ColorMask

}
}