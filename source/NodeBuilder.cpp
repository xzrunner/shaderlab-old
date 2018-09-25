#include "shadergraph/NodeBuilder.h"
#include "shadergraph/Pins.h"

// artistic
#include "shadergraph/node/ColorAddMul.h"
#include "shadergraph/node/ColorMap.h"
#include "shadergraph/node/ReplaceColor.h"
#include "shadergraph/node/Gray.h"
#include "shadergraph/node/ChannelMask.h"
#include "shadergraph/node/ColorMask.h"
// input
#include "shadergraph/node/Time.h"
#include "shadergraph/node/Vector1.h"
#include "shadergraph/node/Vector2.h"
#include "shadergraph/node/Vector3.h"
#include "shadergraph/node/Vector4.h"
#include "shadergraph/node/UV.h"
#include "shadergraph/node/SampleTex2D.h"
#include "shadergraph/node/Tex2DAsset.h"
// master
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Sprite.h"
// math
#include "shadergraph/node/Add.h"
#include "shadergraph/node/Divide.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Power.h"
#include "shadergraph/node/SquareRoot.h"
#include "shadergraph/node/Absolute.h"
#include "shadergraph/node/Exponential.h"
#include "shadergraph/node/Length.h"
#include "shadergraph/node/Log.h"
#include "shadergraph/node/Modulo.h"
#include "shadergraph/node/Negate.h"
#include "shadergraph/node/Normalize.h"
#include "shadergraph/node/Posterize.h"
#include "shadergraph/node/Reciprocal.h"
#include "shadergraph/node/ReciprocalSquareRoot.h"
#include "shadergraph/node/InverseLerp.h"
#include "shadergraph/node/Lerp.h"
#include "shadergraph/node/Remap.h"
// procedural
#include "shadergraph/node/Checkerboard.h"
#include "shadergraph/node/GradientNoise.h"
#include "shadergraph/node/SimpleNoise.h"
#include "shadergraph/node/Voronoi.h"
#include "shadergraph/node/Ellipse.h"
#include "shadergraph/node/Polygon.h"
#include "shadergraph/node/Rectangle.h"
#include "shadergraph/node/RoundedRectangle.h"
// uv
#include "shadergraph/node/Rotate.h"
#include "shadergraph/node/Twirl.h"

#include <node0/SceneNode.h>
#include <node0/CompIdentity.h>
#include <node2/CompTransform.h>
#include <node2/CompBoundingBox.h>
#include <blueprint/CompNode.h>
#include <blueprint/Connecting.h>
#include <blueprint/NodeFactory.h>
#include <blueprint/NodeLayout.h>
#include <blueprint/Pins.h>

namespace sg
{

void NodeBuilder::Init()
{
	// trigger class static init
	sg::node::Time::GetClassName();
}

bp::NodePtr NodeBuilder::Create(std::vector<n0::SceneNodePtr>& nodes,
	                            const std::string& type, const std::string& name,
	                            const sm::vec2& pos, bool is_default)
{
	auto bp_node = bp::NodeFactory::Instance()->Create(type, name);
	if (!bp_node) {
		return nullptr;
	}

	if (is_default) {
		bp_node->SetStyleOnlyTitle(true);
		bp::NodeLayout::UpdateNodeStyle(*bp_node);
	}

	bp_node->SetPos(pos);

	auto node = std::make_shared<n0::SceneNode>();
	auto& cnode = node->AddUniqueComp<bp::CompNode>();
	cnode.SetNode(bp_node);
	auto& ctrans = node->AddUniqueComp<n2::CompTransform>();
	ctrans.SetPosition(*node, pos);
	node->AddUniqueComp<n0::CompIdentity>();
	auto& style = bp_node->GetStyle();
	node->AddUniqueComp<n2::CompBoundingBox>(
		sm::rect(style.width, style.height)
	);

	CreateDefaultInputs(nodes, *bp_node);

	nodes.push_back(node);

	return bp_node;
}

void NodeBuilder::CreateDefaultInputs(std::vector<n0::SceneNodePtr>& nodes, bp::Node& node)
{
	auto type = node.GetClassInfo().GetClassName();
	// artistic
	if (type == node::ColorAddMul::GetClassName())
	{
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, node::ColorAddMul::ID_COL,
			node::Vector4::GetClassName(), "col"))->SetValue({ 0, 0, 0, 1 });
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, node::ColorAddMul::ID_MUL,
			node::Vector4::GetClassName(), "mul"))->SetValue({ 1, 1, 1, 1 });
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, node::ColorAddMul::ID_ADD,
			node::Vector4::GetClassName(), "add"))->SetValue({ 0, 0, 0, 0 });
	}
	else if (type == node::ColorMap::GetClassName())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_COL,
			node::Vector3::GetClassName(), "col"))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_RMAP,
			node::Vector3::GetClassName(), "rmap"))->SetValue({ 1, 0, 0});
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_GMAP,
			node::Vector3::GetClassName(), "gmap"))->SetValue({ 0, 1, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_BMAP,
			node::Vector3::GetClassName(), "bmap"))->SetValue({ 0, 0, 1 });
	}
	else if (type == node::ReplaceColor::GetClassName())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ReplaceColor::ID_COL,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ReplaceColor::ID_FROM,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ReplaceColor::ID_TO,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ReplaceColor::ID_RANGE,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ReplaceColor::ID_FUZZINESS,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Gray::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Vector4::GetClassName());
	}
	else if (type == node::ChannelMask::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Vector1::GetClassName());
	}
	else if (type == node::ColorMask::GetClassName())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMask::ID_COL,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMask::ID_MASK,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ColorMask::ID_RANGE,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ColorMask::ID_FUZZINESS,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	// input
	else if (type == node::SampleTex2D::GetClassName())
	{
		CreateDefault(nodes, node, node::SampleTex2D::ID_TEX, node::Tex2DAsset::GetClassName());
		CreateDefault(nodes, node, node::SampleTex2D::ID_UV, node::UV::GetClassName());
	}
	// master
	else if (type == node::Phong::GetClassName())
	{
		// light
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_POSITION,
			node::Vector3::GetClassName(), "lit_pos"))->SetValue(sm::vec3(1.2f, 1.0f, 2.0f));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_AMBIENT,
			node::Vector3::GetClassName(), "lit_ambient"))->SetValue(sm::vec3(0.2f, 0.2f, 0.2f));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_DIFFUSE,
			node::Vector3::GetClassName(), "lit_diffuse"))->SetValue(sm::vec3(0.5f, 0.5f, 0.5f));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_SPECULAR,
			node::Vector3::GetClassName(), "lit_specular"))->SetValue(sm::vec3(1.0f, 1.0f, 1.0f));
		// material
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_MAT_DIFFUSE,
			node::Vector3::GetClassName(), "mat_diffuse"))->SetValue(sm::vec3(1, 0, 0));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_MAT_SPECULAR,
			node::Vector3::GetClassName(), "mat_specular"))->SetValue(sm::vec3(0, 0.5f, 0));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Phong::ID_MAT_SHININESS,
			node::Vector1::GetClassName(), "mat_shininess"))->SetValue(64.0f);
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_MAT_EMISSION,
			node::Vector3::GetClassName(), "mat_emission"))->SetValue(sm::vec3(0, 0, 0));
		// view
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_VIEW_POS,
			node::Vector3::GetClassName(), "view_pos"))->SetValue(sm::vec3(1.2f, 1.0f, 2.0f));
	}
	else if (type == node::Sprite::GetClassName())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_MUL,
			node::Vector3::GetClassName(), "mul"))->SetValue(sm::vec3(1, 1, 1));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_ADD,
			node::Vector3::GetClassName(), "add"))->SetValue(sm::vec3(0, 0, 0));
	}
	// math
	else if (type == node::Add::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Divide::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Multiply::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Subtract::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Power::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::SquareRoot::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Absolute::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Exponential::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Length::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Log::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Modulo::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Negate::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Normalize::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Posterize::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Reciprocal::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::ReciprocalSquareRoot::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::InverseLerp::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_T,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Lerp::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_T,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Remap::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Remap::ID_IN,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Remap::ID_FROM,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(-1, 1));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Remap::ID_TO,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0, 1));
	}
	// procedural
	else if (type == node::Checkerboard::GetClassName())
	{
		CreateDefault(nodes, node, node::Checkerboard::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Checkerboard::ID_COLOR_A,
			node::Vector3::GetClassName()))->SetValue({ 0.2f, 0.2f, 0.2f });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Checkerboard::ID_COLOR_B,
			node::Vector3::GetClassName()))->SetValue({ 0.7f, 0.7f, 0.7f });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Checkerboard::ID_FREQUENCY,
			node::Vector2::GetClassName()))->SetValue({ 1, 1 });
	}
	else if (type == node::GradientNoise::GetClassName())
	{
		CreateDefault(nodes, node, node::GradientNoise::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::GradientNoise::ID_SCALE,
			node::Vector1::GetClassName()))->SetValue(10);
	}
	else if (type == node::SimpleNoise::GetClassName())
	{
		CreateDefault(nodes, node, node::SimpleNoise::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::SimpleNoise::ID_SCALE,
			node::Vector1::GetClassName()))->SetValue(500);
	}
	else if (type == node::Voronoi::GetClassName())
	{
		CreateDefault(nodes, node, node::Voronoi::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Voronoi::ID_ANGLE_OFFSET,
			node::Vector1::GetClassName()))->SetValue(2);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Voronoi::ID_CELL_DENSITY,
			node::Vector1::GetClassName()))->SetValue(5);
	}
	else if (type == node::Ellipse::GetClassName())
	{
		CreateDefault(nodes, node, node::Ellipse::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Ellipse::ID_WIDTH,
			node::Vector1::GetClassName()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Ellipse::ID_HEIGHT,
			node::Vector1::GetClassName()))->SetValue(0.5f);
	}
	else if (type == node::Polygon::GetClassName())
	{
		CreateDefault(nodes, node, node::Polygon::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Polygon::ID_SIDES,
			node::Vector1::GetClassName()))->SetValue(6);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Polygon::ID_WIDTH,
			node::Vector1::GetClassName()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Polygon::ID_HEIGHT,
			node::Vector1::GetClassName()))->SetValue(0.5f);
	}
	else if (type == node::Rectangle::GetClassName())
	{
		CreateDefault(nodes, node, node::Rectangle::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rectangle::ID_WIDTH,
			node::Vector1::GetClassName()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rectangle::ID_HEIGHT,
			node::Vector1::GetClassName()))->SetValue(0.5f);
	}
	else if (type == node::RoundedRectangle::GetClassName())
	{
		CreateDefault(nodes, node, node::RoundedRectangle::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RoundedRectangle::ID_WIDTH,
			node::Vector1::GetClassName()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RoundedRectangle::ID_HEIGHT,
			node::Vector1::GetClassName()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RoundedRectangle::ID_RADIUS,
			node::Vector1::GetClassName()))->SetValue(0.1f);
	}
	// uv
	else if (type == node::Rotate::GetClassName())
	{
		CreateDefault(nodes, node, node::Rotate::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Rotate::ID_CENTER,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rotate::ID_ROTATION,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Twirl::GetClassName())
	{
		CreateDefault(nodes, node, node::Twirl::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Twirl::ID_CENTER,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Twirl::ID_STRENGTH,
			node::Vector1::GetClassName()))->SetValue(10);
		CreateDefault(nodes, node, node::Twirl::ID_OFFSET, node::Vector2::GetClassName());
	}
}

bp::NodePtr NodeBuilder::CreateDefault(std::vector<n0::SceneNodePtr>& nodes, bp::Node& parent,
	                                   int idx, const std::string& type, const std::string& name)
{
	const float dx = -65;

	auto pos = bp::NodeLayout::GetPinsPos(parent, true, idx);
	pos.x += dx;

	auto child = Create(nodes, type, name, pos, true);
	bp::make_connecting(child->GetAllOutput()[0], parent.GetAllInput()[idx]);

	return child;
}

}