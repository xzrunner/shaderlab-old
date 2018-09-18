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
		AddPins(std::make_shared<Pins>(true, ID_TEX,     PINS_TEXTURE2D, "Tex", *this));
		AddPins(std::make_shared<Pins>(true, ID_COL_MUL, PINS_VECTOR3,   "Mul", *this));
		AddPins(std::make_shared<Pins>(true, ID_COL_ADD, PINS_VECTOR3,   "Add", *this));

		Layout();
	}

public:
	enum InputId
	{
		ID_TEX = 0,
		ID_COL_MUL,
		ID_COL_ADD,
	};

	DECLARE_NODE_CLASS(Sprite)

}; // Sprite

}
}