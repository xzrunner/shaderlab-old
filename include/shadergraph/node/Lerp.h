#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Lerp : public Node
{
public:
	Lerp()
		: Node("Lerp", true)
	{
		AddPins(std::make_shared<Pins>(true, 0, PINS_VECTOR1, "A", *this));
		AddPins(std::make_shared<Pins>(true, 1, PINS_VECTOR1, "B", *this));
		AddPins(std::make_shared<Pins>(true, 2, PINS_VECTOR1, "T", *this));

		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

		Layout();
	}

public:
	enum InputId
	{
		ID_A = 0,
		ID_B,
		ID_T
	};

	DECLARE_NODE_CLASS(Lerp)

}; // Lerp

}
}