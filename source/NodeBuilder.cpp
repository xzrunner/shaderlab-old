#include "shadergraph/NodeBuilder.h"
#include "shadergraph/Pins.h"

// artistic
#include "shadergraph/node/ColorAddMul.h"
#include "shadergraph/node/ColorMap.h"
#include "shadergraph/node/Contrast.h"
#include "shadergraph/node/Hue.h"
#include "shadergraph/node/InvertColors.h"
#include "shadergraph/node/ReplaceColor.h"
#include "shadergraph/node/Saturation.h"
#include "shadergraph/node/WhiteBalance.h"
#include "shadergraph/node/Blend.h"
#include "shadergraph/node/Gray.h"
#include "shadergraph/node/ChannelMask.h"
#include "shadergraph/node/ColorMask.h"
#include "shadergraph/node/NormalBlend.h"
#include "shadergraph/node/NormalCreate.h"
#include "shadergraph/node/NormalStrength.h"
#include "shadergraph/node/NormalUnpack.h"
#include "shadergraph/node/ColorspaceConversion.h"
// channel
#include "shadergraph/node/Combine.h"
#include "shadergraph/node/Flip.h"
#include "shadergraph/node/Split.h"
#include "shadergraph/node/Swizzle.h"
// input
#include "shadergraph/node/Boolean.h"
#include "shadergraph/node/Time.h"
#include "shadergraph/node/Vector1.h"
#include "shadergraph/node/Vector2.h"
#include "shadergraph/node/Vector3.h"
#include "shadergraph/node/Vector4.h"
#include "shadergraph/node/UV.h"
#include "shadergraph/node/Matrix2.h"
#include "shadergraph/node/Matrix3.h"
#include "shadergraph/node/Matrix4.h"
#include "shadergraph/node/SampleTex2D.h"
#include "shadergraph/node/Tex2DAsset.h"
// master
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Sprite.h"
#include "shadergraph/node/Raymarching.h"
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
#include "shadergraph/node/DDX.h"
#include "shadergraph/node/DDY.h"
#include "shadergraph/node/DDXY.h"
#include "shadergraph/node/InverseLerp.h"
#include "shadergraph/node/Lerp.h"
#include "shadergraph/node/Smoothstep.h"
#include "shadergraph/node/MatrixConstruction.h"
#include "shadergraph/node/MatrixDeterminant.h"
#include "shadergraph/node/MatrixSplit.h"
#include "shadergraph/node/MatrixTranspose.h"
#include "shadergraph/node/Clamp.h"
#include "shadergraph/node/Fraction.h"
#include "shadergraph/node/Maximum.h"
#include "shadergraph/node/Minimum.h"
#include "shadergraph/node/OneMinus.h"
#include "shadergraph/node/RandomRange.h"
#include "shadergraph/node/Remap.h"
#include "shadergraph/node/Saturate.h"
#include "shadergraph/node/Ceiling.h"
#include "shadergraph/node/Floor.h"
#include "shadergraph/node/Round.h"
#include "shadergraph/node/Sign.h"
#include "shadergraph/node/Step.h"
#include "shadergraph/node/Truncate.h"
#include "shadergraph/node/Arccosine.h"
#include "shadergraph/node/Arcsine.h"
#include "shadergraph/node/Arctangent.h"
#include "shadergraph/node/Arctangent2.h"
#include "shadergraph/node/Cosine.h"
#include "shadergraph/node/DegreesToRadians.h"
#include "shadergraph/node/HyperbolicCosine.h"
#include "shadergraph/node/HyperbolicSine.h"
#include "shadergraph/node/HyperbolicTangent.h"
#include "shadergraph/node/RadiansToDegrees.h"
#include "shadergraph/node/Sine.h"
#include "shadergraph/node/Tangent.h"
#include "shadergraph/node/CrossProduct.h"
#include "shadergraph/node/Distance.h"
#include "shadergraph/node/DotProduct.h"
#include "shadergraph/node/Projection.h"
#include "shadergraph/node/Rejection.h"
// procedural
#include "shadergraph/node/Checkerboard.h"
#include "shadergraph/node/GradientNoise.h"
#include "shadergraph/node/SimpleNoise.h"
#include "shadergraph/node/Voronoi.h"
#include "shadergraph/node/Ellipse.h"
#include "shadergraph/node/Polygon.h"
#include "shadergraph/node/Rectangle.h"
#include "shadergraph/node/RoundedRectangle.h"
// utility
#include "shadergraph/node/Preview.h"
#include "shadergraph/node/And.h"
#include "shadergraph/node/Or.h"
#include "shadergraph/node/Not.h"
#include "shadergraph/node/Branch.h"
#include "shadergraph/node/Comparison.h"
// uv
#include "shadergraph/node/Flipbook.h"
#include "shadergraph/node/PolarCoordinates.h"
#include "shadergraph/node/RadialShear.h"
#include "shadergraph/node/Rotate.h"
#include "shadergraph/node/Spherize.h"
#include "shadergraph/node/TilingAndOffset.h"
#include "shadergraph/node/Twirl.h"
// SDF
#include "shadergraph/node/Sphere.h"
#include "shadergraph/node/Torus.h"

#include <node0/SceneNode.h>
#include <node0/CompIdentity.h>
#include <node2/CompTransform.h>
#include <node2/CompBoundingBox.h>
#include <blueprint/CompNode.h>
#include <blueprint/Connecting.h>
#include <blueprint/NodeLayout.h>
#include <blueprint/Pins.h>

namespace sg
{

bp::NodePtr NodeBuilder::Create(std::vector<n0::SceneNodePtr>& nodes,
	                            const std::string& type, const std::string& name,
	                            const sm::vec2& pos, bool is_default)
{
	auto rt_type = rttr::type::get_by_name(type);
	assert(rt_type.is_valid());
	auto rt_obj = rt_type.create();
	assert(rt_obj.is_valid());
	auto bp_node = rt_obj.get_value<bp::NodePtr>();
	if (!bp_node) {
		return nullptr;
	}

	if (!name.empty()) {
		bp_node->SetName(name);
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
	auto type = node.get_type();
	// artistic
	if (type == rttr::type::get<node::ColorAddMul>())
	{
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, node::ColorAddMul::ID_COL,
			rttr::type::get<node::Vector4>().get_name().to_string(), "col"))->SetValue({ 0, 0, 0, 1 });
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, node::ColorAddMul::ID_MUL,
			rttr::type::get<node::Vector4>().get_name().to_string(), "mul"))->SetValue({ 1, 1, 1, 1 });
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, node::ColorAddMul::ID_ADD,
			rttr::type::get<node::Vector4>().get_name().to_string(), "add"))->SetValue({ 0, 0, 0, 0 });
	}
	else if (type == rttr::type::get<node::ColorMap>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_COL,
			rttr::type::get<node::Vector3>().get_name().to_string(), "col"))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_RMAP,
			rttr::type::get<node::Vector3>().get_name().to_string(), "rmap"))->SetValue({ 1, 0, 0});
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_GMAP,
			rttr::type::get<node::Vector3>().get_name().to_string(), "gmap"))->SetValue({ 0, 1, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMap::ID_BMAP,
			rttr::type::get<node::Vector3>().get_name().to_string(), "bmap"))->SetValue({ 0, 0, 1 });
	}
	else if (type == rttr::type::get<node::Contrast>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Contrast::ID_INPUT,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Contrast::ID_CONTRAST,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::Hue>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Hue::ID_INPUT,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Hue::ID_OFFSET,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::InvertColors>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::ReplaceColor>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ReplaceColor::ID_COL,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ReplaceColor::ID_FROM,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ReplaceColor::ID_TO,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ReplaceColor::ID_RANGE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ReplaceColor::ID_FUZZINESS,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Saturation>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Saturation::ID_INPUT,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Saturation::ID_SATURATION,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::WhiteBalance>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::WhiteBalance::ID_INPUT,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::WhiteBalance::ID_TEMPERATURE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::WhiteBalance::ID_TINT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Blend>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Blend::ID_BASE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Blend::ID_BLEND,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Blend::ID_OPACITY,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::Gray>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Vector4>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::ChannelMask>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::ColorMask>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMask::ID_COL,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::ColorMask::ID_MASK,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ColorMask::ID_RANGE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::ColorMask::ID_FUZZINESS,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}

	else if (type == rttr::type::get<node::NormalBlend>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::NormalBlend::ID_A,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 1 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::NormalBlend::ID_B,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 1 });
	}
	else if (type == rttr::type::get<node::NormalCreate>())
	{
		CreateDefault(nodes, node, node::NormalCreate::ID_TEX, rttr::type::get<node::Tex2DAsset>().get_name().to_string());
		CreateDefault(nodes, node, node::NormalCreate::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::NormalCreate::ID_OFFSET,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::NormalCreate::ID_STRENGTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(8);
	}
	else if (type == rttr::type::get<node::NormalStrength>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::NormalStrength::ID_INPUT,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 1 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::NormalStrength::ID_STRENGTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::NormalUnpack>())
	{
		std::static_pointer_cast<node::Vector4>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector4>().get_name().to_string()))->SetValue({ 0, 0, 0, 0 });
	}
	else if (type == rttr::type::get<node::ColorspaceConversion>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
	}
	// channel
	else if (type == rttr::type::get<node::Combine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_R,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_G,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Flip>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::Split>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::Swizzle>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string());
	}
	// input
	else if (type == rttr::type::get<node::SampleTex2D>())
	{
		CreateDefault(nodes, node, node::SampleTex2D::ID_TEX, rttr::type::get<node::Tex2DAsset>().get_name().to_string());
		CreateDefault(nodes, node, node::SampleTex2D::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
	}
	// master
	else if (type == rttr::type::get<node::Phong>())
	{
		// light
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_POSITION,
			rttr::type::get<node::Vector3>().get_name().to_string(), "lit_pos"))->SetValue(sm::vec3(1.2f, 1.0f, 2.0f));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_AMBIENT,
			rttr::type::get<node::Vector3>().get_name().to_string(), "lit_ambient"))->SetValue(sm::vec3(0.2f, 0.2f, 0.2f));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_DIFFUSE,
			rttr::type::get<node::Vector3>().get_name().to_string(), "lit_diffuse"))->SetValue(sm::vec3(0.5f, 0.5f, 0.5f));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_LIT_SPECULAR,
			rttr::type::get<node::Vector3>().get_name().to_string(), "lit_specular"))->SetValue(sm::vec3(1.0f, 1.0f, 1.0f));
		// material
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_MAT_DIFFUSE,
			rttr::type::get<node::Vector3>().get_name().to_string(), "mat_diffuse"))->SetValue(sm::vec3(1, 0, 0));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_MAT_SPECULAR,
			rttr::type::get<node::Vector3>().get_name().to_string(), "mat_specular"))->SetValue(sm::vec3(0, 0.5f, 0));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Phong::ID_MAT_SHININESS,
			rttr::type::get<node::Vector1>().get_name().to_string(), "mat_shininess"))->SetValue(64.0f);
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_MAT_EMISSION,
			rttr::type::get<node::Vector3>().get_name().to_string(), "mat_emission"))->SetValue(sm::vec3(0, 0, 0));
		// view
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Phong::ID_VIEW_POS,
			rttr::type::get<node::Vector3>().get_name().to_string(), "view_pos"))->SetValue(sm::vec3(1.2f, 1.0f, 2.0f));
	}
	else if (type == rttr::type::get<node::Sprite>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_MUL,
			rttr::type::get<node::Vector3>().get_name().to_string(), "mul"))->SetValue(sm::vec3(1, 1, 1));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_ADD,
			rttr::type::get<node::Vector3>().get_name().to_string(), "add"))->SetValue(sm::vec3(0, 0, 0));
	}
	else if (type == rttr::type::get<node::Raymarching>())
	{
		CreateDefault(nodes, node, node::Raymarching::ID_UV,  rttr::type::get<node::UV>().get_name().to_string());
		CreateDefault(nodes, node, node::Raymarching::ID_SDF, rttr::type::get<node::Torus>().get_name().to_string());
	}
	// math
	else if (type == rttr::type::get<node::Add>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Divide>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Multiply>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Subtract>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Power>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::SquareRoot>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Absolute>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Exponential>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Length>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Log>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Modulo>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Negate>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Normalize>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Posterize>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Reciprocal>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::ReciprocalSquareRoot>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::DDX>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::DDY>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::DDXY>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::InverseLerp>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_T,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Lerp>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_T,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Smoothstep>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Smoothstep::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Smoothstep::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Smoothstep::ID_T,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::MatrixConstruction>())
	{
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M0, rttr::type::get<node::Vector4>().get_name().to_string());
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M1, rttr::type::get<node::Vector4>().get_name().to_string());
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M2, rttr::type::get<node::Vector4>().get_name().to_string());
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M3, rttr::type::get<node::Vector4>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::MatrixDeterminant>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Matrix2>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::MatrixSplit>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Matrix2>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::MatrixTranspose>())
	{
		CreateDefault(nodes, node, 0, rttr::type::get<node::Matrix2>().get_name().to_string());
	}
	else if (type == rttr::type::get<node::Clamp>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Clamp::ID_IN,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Clamp::ID_MIN,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Clamp::ID_MAX,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::Fraction>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Maximum>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Maximum::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Maximum::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Minimum>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Minimum::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Minimum::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::OneMinus>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::RandomRange>())
	{
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RandomRange::ID_SEED,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RandomRange::ID_MIN,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RandomRange::ID_MAX,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::Remap>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Remap::ID_IN,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Remap::ID_FROM,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(-1, 1));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Remap::ID_TO,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(0, 1));
	}
	else if (type == rttr::type::get<node::Saturate>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Ceiling>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Floor>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Round>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Sign>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Step>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Step::ID_INPUT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Step::ID_EDGE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::Truncate>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Arccosine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::Arcsine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Arctangent>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Arctangent2>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Arctangent2::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Arctangent2::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Cosine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::DegreesToRadians>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::HyperbolicCosine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::HyperbolicSine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::HyperbolicTangent>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::RadiansToDegrees>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Sine>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Tangent>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::CrossProduct>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::CrossProduct::ID_A,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::CrossProduct::ID_B,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
	}
	else if (type == rttr::type::get<node::Distance>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Distance::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Distance::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::DotProduct>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::DotProduct::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::DotProduct::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Projection>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Projection::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Projection::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Rejection>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rejection::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rejection::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	// procedural
	else if (type == rttr::type::get<node::Checkerboard>())
	{
		CreateDefault(nodes, node, node::Checkerboard::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Checkerboard::ID_COLOR_A,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0.2f, 0.2f, 0.2f });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Checkerboard::ID_COLOR_B,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0.7f, 0.7f, 0.7f });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Checkerboard::ID_FREQUENCY,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 1, 1 });
	}
	else if (type == rttr::type::get<node::GradientNoise>())
	{
		CreateDefault(nodes, node, node::GradientNoise::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::GradientNoise::ID_SCALE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(10);
	}
	else if (type == rttr::type::get<node::SimpleNoise>())
	{
		CreateDefault(nodes, node, node::SimpleNoise::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::SimpleNoise::ID_SCALE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(500);
	}
	else if (type == rttr::type::get<node::Voronoi>())
	{
		CreateDefault(nodes, node, node::Voronoi::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Voronoi::ID_ANGLE_OFFSET,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(2);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Voronoi::ID_CELL_DENSITY,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(5);
	}
	else if (type == rttr::type::get<node::Ellipse>())
	{
		CreateDefault(nodes, node, node::Ellipse::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Ellipse::ID_WIDTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Ellipse::ID_HEIGHT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
	}
	else if (type == rttr::type::get<node::Polygon>())
	{
		CreateDefault(nodes, node, node::Polygon::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Polygon::ID_SIDES,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(6);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Polygon::ID_WIDTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Polygon::ID_HEIGHT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
	}
	else if (type == rttr::type::get<node::Rectangle>())
	{
		CreateDefault(nodes, node, node::Rectangle::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rectangle::ID_WIDTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rectangle::ID_HEIGHT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
	}
	else if (type == rttr::type::get<node::RoundedRectangle>())
	{
		CreateDefault(nodes, node, node::RoundedRectangle::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RoundedRectangle::ID_WIDTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RoundedRectangle::ID_HEIGHT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RoundedRectangle::ID_RADIUS,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.1f);
	}
	// utility
	else if (type == rttr::type::get<node::Preview>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::And>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Or>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Not>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Branch>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Branch::ID_PREDICATE,
			rttr::type::get<node::Boolean>().get_name().to_string()))->SetValue(true);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Branch::ID_TRUE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Branch::ID_FALSE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Comparison>())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Comparison::ID_A,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Comparison::ID_B,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	// uv
	else if (type == rttr::type::get<node::Flipbook>())
	{
		CreateDefault(nodes, node, node::Flipbook::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Flipbook::ID_WIDTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Flipbook::ID_HEIGHT,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Flipbook::ID_TILE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::PolarCoordinates>())
	{
		CreateDefault(nodes, node, node::PolarCoordinates::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::PolarCoordinates::ID_CENTER,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::PolarCoordinates::ID_RADIAL_SCALE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::PolarCoordinates::ID_LENGTH_SCALE,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(1);
	}
	else if (type == rttr::type::get<node::RadialShear>())
	{
		CreateDefault(nodes, node, node::RadialShear::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RadialShear::ID_CENTER,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RadialShear::ID_STRENGTH,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 10, 10 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RadialShear::ID_OFFSET,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 0, 0 });
	}
	else if (type == rttr::type::get<node::Rotate>())
	{
		CreateDefault(nodes, node, node::Rotate::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Rotate::ID_CENTER,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rotate::ID_ROTATION,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0);
	}
	else if (type == rttr::type::get<node::Spherize>())
	{
		CreateDefault(nodes, node, node::Spherize::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Spherize::ID_CENTER,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Spherize::ID_STRENGTH,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 10, 10 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Spherize::ID_OFFSET,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 0, 0 });
	}
	else if (type == rttr::type::get<node::TilingAndOffset>())
	{
		CreateDefault(nodes, node, node::TilingAndOffset::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::TilingAndOffset::ID_TILLING,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 1, 1 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::TilingAndOffset::ID_OFFSET,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 0, 0 });
	}
	else if (type == rttr::type::get<node::Twirl>())
	{
		CreateDefault(nodes, node, node::Twirl::ID_UV, rttr::type::get<node::UV>().get_name().to_string());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Twirl::ID_CENTER,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Twirl::ID_STRENGTH,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(10);
		CreateDefault(nodes, node, node::Twirl::ID_OFFSET, rttr::type::get<node::Vector2>().get_name().to_string());
	}
	// sdf
	else if (type == rttr::type::get<node::Sphere>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sphere::ID_POS,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Sphere::ID_RADIUS,
			rttr::type::get<node::Vector1>().get_name().to_string()))->SetValue(0.5f);
	}
	else if (type == rttr::type::get<node::Torus>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Torus::ID_POS,
			rttr::type::get<node::Vector3>().get_name().to_string()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Torus::ID_RADIUS,
			rttr::type::get<node::Vector2>().get_name().to_string()))->SetValue({ 0.2f, 0.8f });
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