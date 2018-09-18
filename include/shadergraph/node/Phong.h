#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Phong : public Node
{
public:
	Phong()
		: Node("Phong", false)
	{
		AddPins(std::make_shared<Pins>(true, ID_LIT_POSITION,  PINS_VECTOR3, "Light Position", *this));
		AddPins(std::make_shared<Pins>(true, ID_LIT_AMBIENT,   PINS_VECTOR3, "Light Ambient", *this));
		AddPins(std::make_shared<Pins>(true, ID_LIT_DIFFUSE,   PINS_VECTOR3, "Light Diffuse", *this));
		AddPins(std::make_shared<Pins>(true, ID_LIT_SPECULAR,  PINS_VECTOR3, "Light Specular", *this));

		AddPins(std::make_shared<Pins>(true, ID_MAT_DIFFUSE,   PINS_VECTOR3, "Material Diffuse", *this));
		AddPins(std::make_shared<Pins>(true, ID_MAT_SPECULAR,  PINS_VECTOR3, "Material Specular", *this));
		AddPins(std::make_shared<Pins>(true, ID_MAT_SHININESS, PINS_VECTOR1, "Material Shininess", *this));
		AddPins(std::make_shared<Pins>(true, ID_MAT_EMISSION,  PINS_VECTOR3, "Material Emission", *this));

		AddPins(std::make_shared<Pins>(true, ID_VIEW_POS,      PINS_VECTOR3, "View pos", *this));

		Layout();
	}

public:
	enum InputId
	{
		ID_LIT_POSITION = 0,
		ID_LIT_AMBIENT,
		ID_LIT_DIFFUSE,
		ID_LIT_SPECULAR,

		ID_MAT_DIFFUSE,
		ID_MAT_SPECULAR,
		ID_MAT_SHININESS,
		ID_MAT_EMISSION,

		ID_VIEW_POS,
	};

	DECLARE_NODE_CLASS(Phong)

}; // Phong

}
}