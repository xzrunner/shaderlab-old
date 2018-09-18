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
		std::shared_ptr<bp::Pins> from, to;

		AddPins(       std::make_shared<Pins>(true, 0, PINS_VECTOR1, "In",   *this));
		AddPins(from = std::make_shared<Pins>(true, 1, PINS_VECTOR2, "From", *this));
		AddPins(to   = std::make_shared<Pins>(true, 2, PINS_VECTOR2, "To",   *this));

		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

		from->SetTypeStatic(true);
		to->SetTypeStatic(true);

		Layout();
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