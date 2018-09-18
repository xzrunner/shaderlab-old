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
		InitPins({
			{ PINS_VECTOR3, "Light Position" },
			{ PINS_VECTOR3, "Light Ambient" },
			{ PINS_VECTOR3, "Light Diffuse" },
			{ PINS_VECTOR3, "Light Specular" },
			{ PINS_VECTOR3, "Material Diffuse" },
			{ PINS_VECTOR3, "Material Specular" },
			{ PINS_VECTOR1, "Material Shininess" },
			{ PINS_VECTOR3, "Material Emission" },
			{ PINS_VECTOR3, "View pos" },
		},{
		});
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