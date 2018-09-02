#include "shadergraph/ShaderGraph.h"
#include "shadergraph/PinsType.h"

#include <painting2/Color.h>
#include <blueprint/RenderSystem.h>

#include <map>

namespace
{

const pt2::Color COL_PINS_VECTOR1   = pt2::Color(132, 228, 231);
const pt2::Color COL_PINS_VECTOR2   = pt2::Color(154, 239, 146);
const pt2::Color COL_PINS_VECTOR3   = pt2::Color(246, 255, 154);
const pt2::Color COL_PINS_VECTOR4   = pt2::Color(251, 203, 244);
const pt2::Color COL_PINS_COLOR     = pt2::Color(251, 203, 244);
const pt2::Color COL_PINS_TEXTURE2D = pt2::Color(255, 139, 139);
const pt2::Color COL_PINS_BOOLEAN   = pt2::Color(148, 129, 230);

}

namespace shadergraph
{

void ShaderGraph::Init()
{
	std::map<int, pt2::Color> pins_type2color;
	pins_type2color.insert({ PINS_VECTOR1,   COL_PINS_VECTOR1 });
	pins_type2color.insert({ PINS_VECTOR2,   COL_PINS_VECTOR2 });
	pins_type2color.insert({ PINS_VECTOR3,   COL_PINS_VECTOR3 });
	pins_type2color.insert({ PINS_VECTOR4,   COL_PINS_VECTOR4 });
	pins_type2color.insert({ PINS_COLOR,     COL_PINS_COLOR });
	pins_type2color.insert({ PINS_TEXTURE2D, COL_PINS_TEXTURE2D });
	pins_type2color.insert({ PINS_BOOLEAN,   COL_PINS_BOOLEAN });
	bp::RenderSystem::Instance()->RegisterPinsColor(pins_type2color);
}

}