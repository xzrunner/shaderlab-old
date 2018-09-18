#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Remap : public Node
{
public:
	Remap()
		: Node("Remap", true)
	{
		InitPins({
			{ PINS_VECTOR1, "In" },
			{ PINS_VECTOR2, "From" },
			{ PINS_VECTOR2, "To" },
		},{
			{ PINS_VECTOR1, "Out", }
		});

		GetAllInput()[ID_FROM]->SetTypeStatic(true);
		GetAllInput()[ID_TO]->SetTypeStatic(true);
	}

public:
	enum InputId
	{
		ID_IN = 0,
		ID_FROM,
		ID_TO
	};

	DECLARE_NODE_CLASS(Remap)

}; // Remap

}
}