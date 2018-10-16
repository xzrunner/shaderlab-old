#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ReplaceColor : public Node
{
public:
	ReplaceColor()
		: Node("ReplaceColor", true)
	{
		InitPins({
			{ PINS_COLOR,   "In" },
			{ PINS_COLOR,   "From" },
			{ PINS_COLOR,   "To" },
			{ PINS_VECTOR1, "Range" },
			{ PINS_VECTOR1, "Fuzziness" },
		},{
			{ PINS_COLOR,   "Out", }
		});
	}

public:
	enum InputID
	{
		ID_COL = 0,
		ID_FROM,
		ID_TO,
		ID_RANGE,
		ID_FUZZINESS,
	};

	RTTR_ENABLE(Node)

}; // ReplaceColor

}
}