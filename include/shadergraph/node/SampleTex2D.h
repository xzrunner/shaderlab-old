#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class SampleTex2D : public Node
{
public:
	SampleTex2D()
		: Node("SampleTex2D", true)
	{
		InitPins({
			{ PINS_TEXTURE2D, "Tex" },
			{ PINS_VECTOR2,   "UV" },
		},{
			{ PINS_VECTOR4, "RGBA" },
			{ PINS_VECTOR1, "R" },
			{ PINS_VECTOR1, "G" },
			{ PINS_VECTOR1, "B" },
			{ PINS_VECTOR1, "A" },
		});
	}

public:
	enum InputID
	{
		ID_TEX = 0,
		ID_UV,
	};

	enum OutputID
	{
		ID_RGBA = 0,
		ID_R,
		ID_G,
		ID_B,
		ID_A,
	};

	DECLARE_NODE_CLASS(SampleTex2D)

}; // SampleTex2D

}
}