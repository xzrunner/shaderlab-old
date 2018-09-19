#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Sprite : public Node
{
public:
	Sprite()
		: Node("Sprite", false)
	{
		InitPins({
			{ PINS_TEXTURE2D, "Tex" },
			{ PINS_VECTOR3,   "Mul" },
			{ PINS_VECTOR3,   "Add" },
		},{
		});
	}

public:
	enum InputID
	{
		ID_TEX = 0,
		ID_COL_MUL,
		ID_COL_ADD,
	};

	DECLARE_NODE_CLASS(Sprite)

}; // Sprite

}
}