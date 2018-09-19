#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class SimpleNoise : public Node
{
public:
	SimpleNoise()
		: Node("SimpleNoise", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Scale" },
		},{
			{ PINS_VECTOR1, "Out", }
		});

		for (auto& p : GetAllInput()) {
			p->SetTypeStatic(true);
		}
		for (auto& p : GetAllOutput()) {
			p->SetTypeStatic(true);
		}
	}

public:
	enum InputId
	{
		ID_UV = 0,
		ID_SCALE,
	};

	DECLARE_NODE_CLASS(SimpleNoise)

}; // SimpleNoise

}
}