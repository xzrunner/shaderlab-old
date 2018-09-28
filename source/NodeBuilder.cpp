#include "shadergraph/NodeBuilder.h"
#include "shadergraph/Pins.h"

// artistic
#include "shadergraph/node/ColorAddMul.h"
#include "shadergraph/node/ColorMap.h"
#include "shadergraph/node/ReplaceColor.h"
#include "shadergraph/node/Gray.h"
#include "shadergraph/node/ChannelMask.h"
#include "shadergraph/node/ColorMask.h"
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
	// channel
	else if (type == node::Combine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_R,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_G,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Combine::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Flip::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Vector1::GetClassName());
	}
	else if (type == node::Split::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Vector1::GetClassName());
	}
	else if (type == node::Swizzle::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Vector1::GetClassName());
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
	else if (type == node::DDX::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::DDY::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::DDXY::GetClassName())
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
	else if (type == node::Smoothstep::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Smoothstep::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Smoothstep::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Smoothstep::ID_T,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::MatrixConstruction::GetClassName())
	{
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M0, node::Vector4::GetClassName());
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M1, node::Vector4::GetClassName());
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M2, node::Vector4::GetClassName());
		CreateDefault(nodes, node, node::MatrixConstruction::ID_M3, node::Vector4::GetClassName());
	}
	else if (type == node::MatrixDeterminant::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Matrix2::GetClassName());
	}
	else if (type == node::MatrixSplit::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Matrix2::GetClassName());
	}
	else if (type == node::MatrixTranspose::GetClassName())
	{
		CreateDefault(nodes, node, 0, node::Matrix2::GetClassName());
	}
	else if (type == node::Clamp::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Clamp::ID_IN,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Clamp::ID_MIN,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Clamp::ID_MAX,
			node::Vector1::GetClassName()))->SetValue(1);
	}
	else if (type == node::Fraction::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Maximum::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Maximum::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Maximum::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Minimum::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Minimum::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Minimum::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::OneMinus::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(1);
	}
	else if (type == node::RandomRange::GetClassName())
	{
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RandomRange::ID_SEED,
			node::Vector2::GetClassName()))->SetValue({ 0, 0 });
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RandomRange::ID_MIN,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::RandomRange::ID_MAX,
			node::Vector1::GetClassName()))->SetValue(1);
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
	else if (type == node::Saturate::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Ceiling::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Floor::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Round::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Sign::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Step::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Step::ID_INPUT,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Step::ID_EDGE,
			node::Vector1::GetClassName()))->SetValue(1);
	}
	else if (type == node::Truncate::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Arccosine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(1);
	}
	else if (type == node::Arcsine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Arctangent::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Arctangent2::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Arctangent2::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Arctangent2::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Cosine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::DegreesToRadians::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::HyperbolicCosine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::HyperbolicSine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::HyperbolicTangent::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::RadiansToDegrees::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Sine::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Tangent::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::CrossProduct::GetClassName())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::CrossProduct::ID_A,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::CrossProduct::ID_B,
			node::Vector3::GetClassName()))->SetValue({ 0, 0, 0 });
	}
	else if (type == node::Distance::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Distance::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Distance::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::DotProduct::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::DotProduct::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::DotProduct::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Projection::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Projection::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Projection::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Rejection::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rejection::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rejection::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
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
	// utility
	else if (type == node::Preview::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::And::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Or::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Not::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Branch::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Branch::ID_PREDICATE,
			node::Boolean::GetClassName()))->SetValue(true);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Branch::ID_TRUE,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Branch::ID_FALSE,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Comparison::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Comparison::ID_A,
			node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Comparison::ID_B,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	// uv
	else if (type == node::Flipbook::GetClassName())
	{
		CreateDefault(nodes, node, node::Flipbook::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Flipbook::ID_WIDTH,
			node::Vector1::GetClassName()))->SetValue(1);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Flipbook::ID_HEIGHT,
			node::Vector1::GetClassName()))->SetValue(1);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Flipbook::ID_TILE,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::PolarCoordinates::GetClassName())
	{
		CreateDefault(nodes, node, node::PolarCoordinates::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::PolarCoordinates::ID_CENTER,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::PolarCoordinates::ID_RADIAL_SCALE,
			node::Vector1::GetClassName()))->SetValue(1);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::PolarCoordinates::ID_LENGTH_SCALE,
			node::Vector1::GetClassName()))->SetValue(1);
	}
	else if (type == node::RadialShear::GetClassName())
	{
		CreateDefault(nodes, node, node::RadialShear::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RadialShear::ID_CENTER,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RadialShear::ID_STRENGTH,
			node::Vector2::GetClassName()))->SetValue({ 10, 10 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::RadialShear::ID_OFFSET,
			node::Vector2::GetClassName()))->SetValue({ 0, 0 });
	}
	else if (type == node::Rotate::GetClassName())
	{
		CreateDefault(nodes, node, node::Rotate::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Rotate::ID_CENTER,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Rotate::ID_ROTATION,
			node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Spherize::GetClassName())
	{
		CreateDefault(nodes, node, node::Spherize::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Spherize::ID_CENTER,
			node::Vector2::GetClassName()))->SetValue(sm::vec2(0.5f, 0.5f));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Spherize::ID_STRENGTH,
			node::Vector2::GetClassName()))->SetValue({ 10, 10 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Spherize::ID_OFFSET,
			node::Vector2::GetClassName()))->SetValue({ 0, 0 });
	}
	else if (type == node::TilingAndOffset::GetClassName())
	{
		CreateDefault(nodes, node, node::TilingAndOffset::ID_UV, node::UV::GetClassName());
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::TilingAndOffset::ID_TILLING,
			node::Vector2::GetClassName()))->SetValue({ 1, 1 });
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::TilingAndOffset::ID_OFFSET,
			node::Vector2::GetClassName()))->SetValue({ 0, 0 });
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