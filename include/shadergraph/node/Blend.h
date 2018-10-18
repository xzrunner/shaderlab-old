#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

#include <shaderweaver/node/Blend.h>

namespace sg
{
namespace node
{

class Blend : public Node
{
public:
	Blend()
		: Node("Blend", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "Base" },
			{ PINS_DYNAMIC_VECTOR, "Blend" },
			{ PINS_VECTOR1,        "Opacity" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	auto GetMode() const { return m_mode.mode; }
	void SetMode(uint32_t mode) { m_mode.mode = mode; }

	enum InputID
	{
		ID_BASE = 0,
		ID_BLEND,
		ID_OPACITY,
	};

private:
	PropBlendMode m_mode = sw::node::Blend::MODE_BURN;

	RTTR_ENABLE(Node)

}; // Blend

}
}