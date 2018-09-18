#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Add : public Node
{
public:
	Add()
		: Node("Add", true)
	{
		AddPins(std::make_shared<Pins>(true,  0, PINS_VECTOR1, "A", *this));
		AddPins(std::make_shared<Pins>(true,  1, PINS_VECTOR1, "B", *this));

		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

		Layout();
	}

	DECLARE_NODE_CLASS(Add)

}; // Add

}
}