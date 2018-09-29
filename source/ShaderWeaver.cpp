#include "shadergraph/ShaderWeaver.h"
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

#include <blueprint/Node.h>
#include <blueprint/Pins.h>
#include <blueprint/Connecting.h>
#include <blueprint/CompNode.h>

#include <shaderweaver/Evaluator.h>
// artistic
#include <shaderweaver/node/ColorAddMul.h>
#include <shaderweaver/node/ColorMap.h>
#include <shaderweaver/node/Contrast.h>
#include <shaderweaver/node/Hue.h>
#include <shaderweaver/node/InvertColors.h>
#include <shaderweaver/node/ReplaceColor.h>
#include <shaderweaver/node/Saturation.h>
#include <shaderweaver/node/WhiteBalance.h>
#include <shaderweaver/node/Blend.h>
#include <shaderweaver/node/Gray.h>
#include <shaderweaver/node/ChannelMask.h>
#include <shaderweaver/node/ColorMask.h>
#include <shaderweaver/node/NormalBlend.h>
#include <shaderweaver/node/NormalCreate.h>
#include <shaderweaver/node/NormalStrength.h>
#include <shaderweaver/node/NormalUnpack.h>
#include <shaderweaver/node/ColorspaceConversion.h>
// channel
#include <shaderweaver/node/Combine.h>
#include <shaderweaver/node/Flip.h>
#include <shaderweaver/node/Split.h>
#include <shaderweaver/node/Swizzle.h>
// input
#include <shaderweaver/node/Boolean.h>
#include <shaderweaver/node/Time.h>
#include <shaderweaver/node/Vector1.h>
#include <shaderweaver/node/Vector2.h>
#include <shaderweaver/node/Vector3.h>
#include <shaderweaver/node/Vector4.h>
#include <shaderweaver/node/UV.h>
#include <shaderweaver/node/Matrix2.h>
#include <shaderweaver/node/Matrix3.h>
#include <shaderweaver/node/Matrix4.h>
#include <shaderweaver/node/SampleTex2D.h>
// master
#include <shaderweaver/node/Phong.h>
// math
#include <shaderweaver/node/Assign.h>
#include <shaderweaver/node/Add.h>
#include <shaderweaver/node/Divide.h>
#include <shaderweaver/node/Multiply.h>
#include <shaderweaver/node/Subtract.h>
#include <shaderweaver/node/Power.h>
#include <shaderweaver/node/SquareRoot.h>
#include <shaderweaver/node/Absolute.h>
#include <shaderweaver/node/Exponential.h>
#include <shaderweaver/node/Length.h>
#include <shaderweaver/node/Log.h>
#include <shaderweaver/node/Modulo.h>
#include <shaderweaver/node/Negate.h>
#include <shaderweaver/node/Normalize.h>
#include <shaderweaver/node/Posterize.h>
#include <shaderweaver/node/Reciprocal.h>
#include <shaderweaver/node/ReciprocalSquareRoot.h>
#include <shaderweaver/node/DDX.h>
#include <shaderweaver/node/DDY.h>
#include <shaderweaver/node/DDXY.h>
#include <shaderweaver/node/InverseLerp.h>
#include <shaderweaver/node/Lerp.h>
#include <shaderweaver/node/Smoothstep.h>
#include <shaderweaver/node/MatrixConstruction.h>
#include <shaderweaver/node/MatrixDeterminant.h>
#include <shaderweaver/node/MatrixSplit.h>
#include <shaderweaver/node/MatrixTranspose.h>
#include <shaderweaver/node/Clamp.h>
#include <shaderweaver/node/Fraction.h>
#include <shaderweaver/node/Maximum.h>
#include <shaderweaver/node/Minimum.h>
#include <shaderweaver/node/OneMinus.h>
#include <shaderweaver/node/RandomRange.h>
#include <shaderweaver/node/Remap.h>
#include <shaderweaver/node/Saturate.h>
#include <shaderweaver/node/Ceiling.h>
#include <shaderweaver/node/Floor.h>
#include <shaderweaver/node/Round.h>
#include <shaderweaver/node/Sign.h>
#include <shaderweaver/node/Step.h>
#include <shaderweaver/node/Truncate.h>
#include <shaderweaver/node/Arccosine.h>
#include <shaderweaver/node/Arcsine.h>
#include <shaderweaver/node/Arctangent.h>
#include <shaderweaver/node/Arctangent2.h>
#include <shaderweaver/node/Cosine.h>
#include <shaderweaver/node/DegreesToRadians.h>
#include <shaderweaver/node/HyperbolicCosine.h>
#include <shaderweaver/node/HyperbolicSine.h>
#include <shaderweaver/node/HyperbolicTangent.h>
#include <shaderweaver/node/RadiansToDegrees.h>
#include <shaderweaver/node/Sine.h>
#include <shaderweaver/node/Tangent.h>
#include <shaderweaver/node/CrossProduct.h>
#include <shaderweaver/node/Distance.h>
#include <shaderweaver/node/DotProduct.h>
#include <shaderweaver/node/Projection.h>
#include <shaderweaver/node/Rejection.h>
// procedural
#include <shaderweaver/node/Checkerboard.h>
#include <shaderweaver/node/GradientNoise.h>
#include <shaderweaver/node/SimpleNoise.h>
#include <shaderweaver/node/Voronoi.h>
#include <shaderweaver/node/Ellipse.h>
#include <shaderweaver/node/Polygon.h>
#include <shaderweaver/node/Rectangle.h>
#include <shaderweaver/node/RoundedRectangle.h>
// utility
#include <shaderweaver/node/Input.h>
#include <shaderweaver/node/Output.h>
#include <shaderweaver/node/Uniform.h>
#include <shaderweaver/node/PositionTransOld.h>
#include <shaderweaver/node/PositionTrans.h>
#include <shaderweaver/node/FragPosTrans.h>
#include <shaderweaver/node/NormalTrans.h>
#include <shaderweaver/node/And.h>
#include <shaderweaver/node/Or.h>
#include <shaderweaver/node/Not.h>
#include <shaderweaver/node/Branch.h>
#include <shaderweaver/node/Comparison.h>
// uv
#include <shaderweaver/node/Flipbook.h>
#include <shaderweaver/node/PolarCoordinates.h>
#include <shaderweaver/node/RadialShear.h>
#include <shaderweaver/node/Rotate.h>
#include <shaderweaver/node/Spherize.h>
#include <shaderweaver/node/TilingAndOffset.h>
#include <shaderweaver/node/Twirl.h>

#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>
#include <painting2/Shader.h>
#include <painting3/Shader.h>
#include <node0/SceneNode.h>
#include <facade/Image.h>

#include <assert.h>

namespace
{

void debug_print(const sw::Evaluator& vert, const sw::Evaluator& frag)
{
	printf("//////////////////////////////////////////////////////////////////////////\n");
	printf("%s\n", vert.GetShaderStr().c_str());
	printf("//////////////////////////////////////////////////////////////////////////\n");
	printf("%s\n", frag.GetShaderStr().c_str());
	printf("//////////////////////////////////////////////////////////////////////////\n");
}

void add_vert_varying(std::vector<sw::NodePtr>& nodes, std::vector<sw::NodePtr>& cache_nodes, const std::string& name, uint32_t type)
{
	auto vert_in = std::make_shared<sw::node::Input>(name, type);
	auto vert_out = std::make_shared<sw::node::Output>("v_" + name, type);
	sw::make_connecting({ vert_in, 0 }, { vert_out, 0 });
	nodes.push_back(vert_out);

	cache_nodes.push_back(vert_in);
}

}

namespace sg
{

ShaderWeaver::ShaderWeaver(VertType vert_type, const bp::Node& frag_node, bool debug_print)
	: m_debug_print(debug_print)
{
	switch (vert_type)
	{
	case VERT_SHAPE:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib("position", 2, 4, 8, 0));

		// vert

		auto proj  = std::make_shared<sw::node::Uniform>("u_projection",  sw::t_mat4);
		auto view  = std::make_shared<sw::node::Uniform>("u_view",        sw::t_mat4);
		auto model = std::make_shared<sw::node::Uniform>("u_model",       sw::t_mat4);
		m_cached_nodes.push_back(proj);
		m_cached_nodes.push_back(view);
		m_cached_nodes.push_back(model);

		auto position = std::make_shared<sw::node::Input>("position", sw::t_pos2);
		m_cached_nodes.push_back(position);

		auto pos_trans = std::make_shared<sw::node::PositionTrans>(2);
		sw::make_connecting({ proj, 0 },     { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },     { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },    { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 }, { pos_trans, sw::node::PositionTrans::ID_POS });
		m_vert_nodes.push_back(pos_trans);

		// frag
		m_frag_node = CreateWeaverNode(frag_node);
	}
		break;
	case VERT_SPRITE:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib("position", 2, 4, 16, 0));
		m_layout.push_back(ur::VertexAttrib("texcoord", 2, 4, 16, 8));

		// vert

		auto proj  = std::make_shared<sw::node::Uniform>("u_projection",  sw::t_mat4);
		auto view  = std::make_shared<sw::node::Uniform>("u_view",        sw::t_mat4);
		auto model = std::make_shared<sw::node::Uniform>("u_model",       sw::t_mat4);
		m_cached_nodes.push_back(proj);
		m_cached_nodes.push_back(view);
		m_cached_nodes.push_back(model);

		auto position = std::make_shared<sw::node::Input>("position", sw::t_pos2);
		m_cached_nodes.push_back(position);

		auto pos_trans = std::make_shared<sw::node::PositionTrans>(2);
		sw::make_connecting({ proj, 0 },     { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },     { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },    { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 }, { pos_trans, sw::node::PositionTrans::ID_POS });
		m_vert_nodes.push_back(pos_trans);

		add_vert_varying(m_vert_nodes, m_cached_nodes, "texcoord", sw::t_uv);

		// frag
		m_frag_node = CreateWeaverNode(frag_node);
	}
		break;
	case VERT_PHONG:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib("position", 3, 4, 32, 0));
		m_layout.push_back(ur::VertexAttrib("normal",   3, 4, 32, 12));
		m_layout.push_back(ur::VertexAttrib("texcoord", 2, 4, 32, 24));

		// vert

		auto projection = std::make_shared<sw::node::Uniform>("u_projection", sw::t_mat4);
		auto view       = std::make_shared<sw::node::Uniform>("u_view",       sw::t_mat4);
		auto model      = std::make_shared<sw::node::Uniform>("u_model",      sw::t_mat4);
		m_cached_nodes.push_back(projection);
		m_cached_nodes.push_back(view);
		m_cached_nodes.push_back(model);

		auto position = std::make_shared<sw::node::Input>("position", sw::t_flt3);
		auto normal   = std::make_shared<sw::node::Input>("normal",   sw::t_nor3);
		m_cached_nodes.push_back(position);
		m_cached_nodes.push_back(normal);

		auto pos_trans = std::make_shared<sw::node::PositionTrans>(3);
		sw::make_connecting({ projection, 0 }, { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },       { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },      { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 },   { pos_trans, sw::node::PositionTrans::ID_POS });
		m_vert_nodes.push_back(pos_trans);

		auto frag_pos_trans = std::make_shared<sw::node::FragPosTrans>();
		sw::make_connecting({ model, 0 },    { frag_pos_trans, sw::node::FragPosTrans::ID_MODEL });
		sw::make_connecting({ position, 0 }, { frag_pos_trans, sw::node::FragPosTrans::ID_POS });
		m_vert_nodes.push_back(frag_pos_trans);

		auto norm_trans = std::make_shared<sw::node::NormalTrans>();
		sw::make_connecting({ model, 0 },  { norm_trans, sw::node::NormalTrans::ID_MODEL });
		sw::make_connecting({ normal, 0 }, { norm_trans, sw::node::NormalTrans::ID_NORM });
		m_vert_nodes.push_back(norm_trans);

		add_vert_varying(m_vert_nodes, m_cached_nodes, "frag_pos", sw::t_flt3);
		add_vert_varying(m_vert_nodes, m_cached_nodes, "normal",   sw::t_nor3);
		add_vert_varying(m_vert_nodes, m_cached_nodes, "texcoord", sw::t_uv);

		// frag

		auto phong = CreateWeaverNode(frag_node);

		auto frag_in_pos = std::make_shared<sw::node::Input>("v_frag_pos", sw::t_flt3);
		auto frag_in_nor = std::make_shared<sw::node::Input>("v_normal", sw::t_nor3);
		m_cached_nodes.push_back(frag_in_pos);
		m_cached_nodes.push_back(frag_in_nor);
		sw::make_connecting({ frag_in_pos, 0 }, { phong, sw::node::Phong::ID_FRAG_POS });
		sw::make_connecting({ frag_in_nor, 0 }, { phong, sw::node::Phong::ID_NORMAL });

		m_frag_node = phong;
	}
		break;
	default:
		assert(0);
	}
}

std::shared_ptr<pt2::Shader> ShaderWeaver::CreateShader(pt2::WindowContext& wc) const
{
	sw::Evaluator vert(m_vert_nodes, sw::ST_VERT);
	sw::Evaluator frag({ m_frag_node }, sw::ST_FRAG);

	if (m_debug_print) {
		debug_print(vert, frag);
	}

	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	auto shader = std::make_shared<pt2::Shader>(wc, &rc, CreateShaderParams(vert, frag));

	shader->SetUsedTextures(m_texture_ids);

	return shader;
}

std::shared_ptr<pt3::Shader> ShaderWeaver::CreateShader(pt3::WindowContext& wc) const
{
	sw::Evaluator vert(m_vert_nodes, sw::ST_VERT);
	sw::Evaluator frag({ m_frag_node }, sw::ST_FRAG);

	if (m_debug_print) {
		debug_print(vert, frag);
	}

	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	auto shader = std::make_shared<pt3::Shader>(wc, &rc, CreateShaderParams(vert, frag));

	shader->SetUsedTextures(m_texture_ids);

	return shader;
}

sw::NodePtr ShaderWeaver::CreateWeaverNode(const bp::Node& node)
{
	sw::NodePtr dst = nullptr;

	int id = node.TypeID();
	// artistic
	if (id == bp::GetNodeTypeID<node::ColorAddMul>())
	{
		auto& src = static_cast<const node::ColorAddMul&>(node);
		dst = std::make_shared<sw::node::ColorAddMul>();
		sw::make_connecting(
			CreateInputChild(src, node::ColorAddMul::ID_COL),
			{ dst, sw::node::ColorAddMul::ID_COL }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorAddMul::ID_MUL),
			{ dst, sw::node::ColorAddMul::ID_MUL }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorAddMul::ID_ADD),
			{ dst, sw::node::ColorAddMul::ID_ADD }
		);
	}
	else if (id == bp::GetNodeTypeID<node::ColorMap>())
	{
		auto& src = static_cast<const node::ColorMap&>(node);
		dst = std::make_shared<sw::node::ColorMap>();
		sw::make_connecting(
			CreateInputChild(src, node::ColorMap::ID_COL),
			{ dst, sw::node::ColorMap::ID_COL }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorMap::ID_RMAP),
			{ dst, sw::node::ColorMap::ID_RMAP }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorMap::ID_GMAP),
			{ dst, sw::node::ColorMap::ID_GMAP }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorMap::ID_BMAP),
			{ dst, sw::node::ColorMap::ID_BMAP }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Contrast>())
	{
		auto& src = static_cast<const node::Contrast&>(node);
		dst = std::make_shared<sw::node::Contrast>();
		sw::make_connecting(
			CreateInputChild(src, node::Contrast::ID_INPUT),
			{ dst, sw::node::Contrast::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Contrast::ID_CONTRAST),
			{ dst, sw::node::Contrast::ID_CONTRAST }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Hue>())
	{
		auto& src = static_cast<const node::Hue&>(node);
		dst = std::make_shared<sw::node::Hue>(src.IsRadians());
		sw::make_connecting(
			CreateInputChild(src, node::Hue::ID_INPUT),
			{ dst, sw::node::Hue::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Hue::ID_OFFSET),
			{ dst, sw::node::Hue::ID_OFFSET }
		);
	}
	else if (id == bp::GetNodeTypeID<node::InvertColors>())
	{
		auto& src = static_cast<const node::InvertColors&>(node);
		dst = std::make_shared<sw::node::InvertColors>(src.GetChannels());
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::ReplaceColor>())
	{
		auto& src = static_cast<const node::ReplaceColor&>(node);
		dst = std::make_shared<sw::node::ReplaceColor>();
		sw::make_connecting(
			CreateInputChild(src, node::ReplaceColor::ID_COL),
			{ dst, sw::node::ReplaceColor::ID_COL }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ReplaceColor::ID_FROM),
			{ dst, sw::node::ReplaceColor::ID_FROM }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ReplaceColor::ID_TO),
			{ dst, sw::node::ReplaceColor::ID_TO }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ReplaceColor::ID_RANGE),
			{ dst, sw::node::ReplaceColor::ID_RANGE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ReplaceColor::ID_FUZZINESS),
			{ dst, sw::node::ReplaceColor::ID_FUZZINESS }
		);
	}

	else if (id == bp::GetNodeTypeID<node::Saturation>())
	{
		auto& src = static_cast<const node::Saturation&>(node);
		dst = std::make_shared<sw::node::Saturation>();
		sw::make_connecting(
			CreateInputChild(src, node::Saturation::ID_INPUT),
			{ dst, sw::node::Saturation::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Saturation::ID_SATURATION),
			{ dst, sw::node::Saturation::ID_SATURATION }
		);
	}
	else if (id == bp::GetNodeTypeID<node::WhiteBalance>())
	{
		auto& src = static_cast<const node::WhiteBalance&>(node);
		dst = std::make_shared<sw::node::WhiteBalance>();
		sw::make_connecting(
			CreateInputChild(src, node::WhiteBalance::ID_INPUT),
			{ dst, sw::node::WhiteBalance::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::WhiteBalance::ID_TEMPERATURE),
			{ dst, sw::node::WhiteBalance::ID_TEMPERATURE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::WhiteBalance::ID_TINT),
			{ dst, sw::node::WhiteBalance::ID_TINT }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Blend>())
	{
		auto& src = static_cast<const node::Blend&>(node);
		dst = std::make_shared<sw::node::Blend>(src.GetMode());
		sw::make_connecting(
			CreateInputChild(src, node::Blend::ID_BASE),
			{ dst, sw::node::Blend::ID_BASE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Blend::ID_BLEND),
			{ dst, sw::node::Blend::ID_BLEND }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Blend::ID_OPACITY),
			{ dst, sw::node::Blend::ID_OPACITY }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Gray>())
	{
		auto& src = static_cast<const node::Gray&>(node);
		dst = std::make_shared<sw::node::Gray>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::ChannelMask>())
	{
		auto& src = static_cast<const node::ChannelMask&>(node);
		dst = std::make_shared<sw::node::ChannelMask>(src.GetChannels());
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::ColorMask>())
	{
		auto& src = static_cast<const node::ColorMask&>(node);
		dst = std::make_shared<sw::node::ColorMask>();
		sw::make_connecting(
			CreateInputChild(src, node::ColorMask::ID_COL),
			{ dst, sw::node::ColorMask::ID_COL }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorMask::ID_MASK),
			{ dst, sw::node::ColorMask::ID_MASK }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorMask::ID_RANGE),
			{ dst, sw::node::ColorMask::ID_RANGE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::ColorMask::ID_FUZZINESS),
			{ dst, sw::node::ColorMask::ID_FUZZINESS }
		);
	}
	else if (id == bp::GetNodeTypeID<node::NormalBlend>())
	{
		auto& src = static_cast<const node::NormalBlend&>(node);
		dst = std::make_shared<sw::node::NormalBlend>();
		sw::make_connecting(
			CreateInputChild(src, node::NormalBlend::ID_A),
			{ dst, sw::node::NormalBlend::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::NormalBlend::ID_B),
			{ dst, sw::node::NormalBlend::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::NormalCreate>())
	{
		auto& src = static_cast<const node::NormalCreate&>(node);
		dst = std::make_shared<sw::node::NormalCreate>();
		sw::make_connecting(
			CreateInputChild(src, node::NormalCreate::ID_TEX),
			{ dst, sw::node::NormalCreate::ID_TEX }
		);
		sw::make_connecting(
			CreateInputChild(src, node::NormalCreate::ID_UV),
			{ dst, sw::node::NormalCreate::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::NormalCreate::ID_OFFSET),
			{ dst, sw::node::NormalCreate::ID_OFFSET }
		);
		sw::make_connecting(
			CreateInputChild(src, node::NormalCreate::ID_STRENGTH),
			{ dst, sw::node::NormalCreate::ID_STRENGTH }
		);
	}
	else if (id == bp::GetNodeTypeID<node::NormalStrength>())
	{
		auto& src = static_cast<const node::NormalStrength&>(node);
		dst = std::make_shared<sw::node::NormalStrength>();
		sw::make_connecting(
			CreateInputChild(src, node::NormalStrength::ID_INPUT),
			{ dst, sw::node::NormalStrength::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::NormalStrength::ID_STRENGTH),
			{ dst, sw::node::NormalStrength::ID_STRENGTH }
		);
	}
	else if (id == bp::GetNodeTypeID<node::NormalUnpack>())
	{
		auto& src = static_cast<const node::NormalUnpack&>(node);
		dst = std::make_shared<sw::node::NormalUnpack>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::ColorspaceConversion>())
	{
		auto& src = static_cast<const node::ColorspaceConversion&>(node);
		node::ColorspaceConversion::ColorType f, t;
		src.GetTypes(f, t);
		dst = std::make_shared<sw::node::ColorspaceConversion>(
			static_cast<sw::node::ColorspaceConversion::ColorType>(f),
			static_cast<sw::node::ColorspaceConversion::ColorType>(t)
		);
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	// channel
	else if (id == bp::GetNodeTypeID<node::Combine>())
	{
		auto& src = static_cast<const node::Combine&>(node);
		dst = std::make_shared<sw::node::Combine>();
		sw::make_connecting(
			CreateInputChild(src, node::Combine::ID_R),
			{ dst, sw::node::Combine::ID_R }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Combine::ID_G),
			{ dst, sw::node::Combine::ID_G }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Combine::ID_B),
			{ dst, sw::node::Combine::ID_B }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Combine::ID_A),
			{ dst, sw::node::Combine::ID_A }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Flip>())
	{
		auto& src = static_cast<const node::Flip&>(node);
		dst = std::make_shared<sw::node::Flip>(src.GetChannels());
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Split>())
	{
		auto& src = static_cast<const node::Split&>(node);
		dst = std::make_shared<sw::node::Split>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Swizzle>())
	{
		auto& src = static_cast<const node::Swizzle&>(node);
		uint32_t channels[4];
		src.GetChannels(channels);
		dst = std::make_shared<sw::node::Swizzle>(channels);
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	// input
	else if (id == bp::GetNodeTypeID<node::Boolean>())
	{
		auto& src = static_cast<const node::Boolean&>(node);
		dst = std::make_shared<sw::node::Boolean>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::Time>())
	{
		dst = std::make_shared<sw::node::Time>();
	}
	else if (id == bp::GetNodeTypeID<node::Vector1>())
	{
		auto& src = static_cast<const node::Vector1&>(node);
		dst = std::make_shared<sw::node::Vector1>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::Vector2>())
	{
		auto& src = static_cast<const node::Vector2&>(node);
		dst = std::make_shared<sw::node::Vector2>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::Vector3>())
	{
		auto& src = static_cast<const node::Vector3&>(node);
		dst = std::make_shared<sw::node::Vector3>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::Vector4>())
	{
		auto& src = static_cast<const node::Vector4&>(node);
		dst = std::make_shared<sw::node::Vector4>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::UV>())
	{
		auto& src = static_cast<const node::UV&>(node);
		dst = std::make_shared<sw::node::UV>(src.GetName());
	}
	else if (id == bp::GetNodeTypeID<node::Matrix2>())
	{
		auto& src = static_cast<const node::Matrix2&>(node);
		dst = std::make_shared<sw::node::Matrix2>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::Matrix3>())
	{
		auto& src = static_cast<const node::Matrix3&>(node);
		dst = std::make_shared<sw::node::Matrix3>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::Matrix4>())
	{
		auto& src = static_cast<const node::Matrix4&>(node);
		dst = std::make_shared<sw::node::Matrix4>(src.GetName(), src.GetValue());
	}
	else if (id == bp::GetNodeTypeID<node::SampleTex2D>())
	{
		auto& src = static_cast<const node::SampleTex2D&>(node);
		dst = std::make_shared<sw::node::SampleTex2D>();
		sw::make_connecting(
			CreateInputChild(src, node::SampleTex2D::ID_TEX),
			{ dst, sw::node::SampleTex2D::ID_TEX }
		);
		sw::make_connecting(
			CreateInputChild(src, node::SampleTex2D::ID_UV),
			{ dst, sw::node::SampleTex2D::ID_UV }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Tex2DAsset>())
	{
		auto& src = static_cast<const node::Tex2DAsset&>(node);
		m_texture_names.push_back(src.GetName());
		auto& img = src.GetImage();
		if (img) {
			m_texture_ids.push_back(img->GetTexID());
		}
		dst = std::make_shared<sw::node::Uniform>(src.GetName(), sw::t_tex2d);
	}
	// master
	else if (id == bp::GetNodeTypeID<node::Phong>())
	{
		dst = std::make_shared<sw::node::Phong>();

		auto& src = static_cast<const node::Phong&>(node);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_LIT_POSITION),
			{ dst, sw::node::Phong::ID_LIGHT_POSITION }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_LIT_AMBIENT),
			{ dst, sw::node::Phong::ID_LIGHT_AMBIENT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_LIT_DIFFUSE),
			{ dst, sw::node::Phong::ID_LIGHT_DIFFUSE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_LIT_SPECULAR),
			{ dst, sw::node::Phong::ID_LIGHT_SPECULAR }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_MAT_DIFFUSE),
			{ dst, sw::node::Phong::ID_MATERIAL_DIFFUSE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_MAT_SPECULAR),
			{ dst, sw::node::Phong::ID_MATERIAL_SPECULAR }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_MAT_SHININESS),
			{ dst, sw::node::Phong::ID_MATERIAL_SHININESS }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_MAT_EMISSION),
			{ dst, sw::node::Phong::ID_MATERIAL_EMISSION }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Phong::ID_VIEW_POS),
			{ dst, sw::node::Phong::ID_VIEW_POS }
		);
	}
	// math
	else if (id == bp::GetNodeTypeID<node::Add>())
	{
		auto& src = static_cast<const node::Add&>(node);
		dst = std::make_shared<sw::node::Add>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::Add::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::Add::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::Divide>())
	{
		auto& src = static_cast<const node::Divide&>(node);
		dst = std::make_shared<sw::node::Divide>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::Divide::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::Divide::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::Multiply>())
	{
		auto& src = static_cast<const node::Multiply&>(node);
		dst = std::make_shared<sw::node::Multiply>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::Multiply::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::Multiply::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::Subtract>())
	{
		auto& src = static_cast<const node::Subtract&>(node);
		dst = std::make_shared<sw::node::Subtract>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::Subtract::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::Subtract::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::Power>())
	{
		auto& src = static_cast<const node::Power&>(node);
		dst = std::make_shared<sw::node::Power>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::Power::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::Power::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::SquareRoot>())
	{
		auto& src = static_cast<const node::SquareRoot&>(node);
		dst = std::make_shared<sw::node::SquareRoot>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Absolute>())
	{
		auto& src = static_cast<const node::Absolute&>(node);
		dst = std::make_shared<sw::node::Absolute>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Exponential>())
	{
		auto& src = static_cast<const node::Exponential&>(node);
		dst = std::make_shared<sw::node::Exponential>(
			static_cast<sw::node::Exponential::BaseType>(src.GetType())
		);
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Length>())
	{
		auto& src = static_cast<const node::Length&>(node);
		dst = std::make_shared<sw::node::Length>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Log>())
	{
		auto& src = static_cast<const node::Log&>(node);
		dst = std::make_shared<sw::node::Log>(
			static_cast<sw::node::Log::BaseType>(src.GetType())
		);
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Modulo>())
	{
		auto& src = static_cast<const node::Modulo&>(node);
		dst = std::make_shared<sw::node::Modulo>();
		sw::make_connecting(
			CreateInputChild(src, node::Modulo::ID_A),
			{ dst, sw::node::Modulo::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Modulo::ID_B),
			{ dst, sw::node::Modulo::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Negate>())
	{
		auto& src = static_cast<const node::Negate&>(node);
		dst = std::make_shared<sw::node::Negate>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Normalize>())
	{
		auto& src = static_cast<const node::Normalize&>(node);
		dst = std::make_shared<sw::node::Normalize>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Posterize>())
	{
		auto& src = static_cast<const node::Posterize&>(node);
		dst = std::make_shared<sw::node::Posterize>();
		sw::make_connecting(
			CreateInputChild(src, node::Posterize::ID_INPUT),
			{ dst, sw::node::Posterize::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Posterize::ID_STEPS),
			{ dst, sw::node::Posterize::ID_STEPS }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Reciprocal>())
	{
		auto& src = static_cast<const node::Reciprocal&>(node);
		dst = std::make_shared<sw::node::Reciprocal>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::ReciprocalSquareRoot>())
	{
		auto& src = static_cast<const node::ReciprocalSquareRoot&>(node);
		dst = std::make_shared<sw::node::ReciprocalSquareRoot>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::DDX>())
	{
		auto& src = static_cast<const node::DDX&>(node);
		dst = std::make_shared<sw::node::DDX>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::DDY>())
	{
		auto& src = static_cast<const node::DDY&>(node);
		dst = std::make_shared<sw::node::DDY>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::DDXY>())
	{
		auto& src = static_cast<const node::DDXY&>(node);
		dst = std::make_shared<sw::node::DDXY>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::InverseLerp>())
	{
		auto& src = static_cast<const node::InverseLerp&>(node);
		dst = std::make_shared<sw::node::InverseLerp>();
		sw::make_connecting(
			CreateInputChild(src, node::InverseLerp::ID_A),
			{ dst, sw::node::InverseLerp::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::InverseLerp::ID_B),
			{ dst, sw::node::InverseLerp::ID_B }
		);
		sw::make_connecting(
			CreateInputChild(src, node::InverseLerp::ID_T),
			{ dst, sw::node::InverseLerp::ID_T }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Lerp>())
	{
		auto& src = static_cast<const node::Lerp&>(node);
		dst = std::make_shared<sw::node::Lerp>();
		sw::make_connecting(
			CreateInputChild(src, node::Lerp::ID_A),
			{ dst, sw::node::Lerp::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Lerp::ID_B),
			{ dst, sw::node::Lerp::ID_B }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Lerp::ID_T),
			{ dst, sw::node::Lerp::ID_T }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Smoothstep>())
	{
		auto& src = static_cast<const node::Smoothstep&>(node);
		dst = std::make_shared<sw::node::Smoothstep>();
		sw::make_connecting(
			CreateInputChild(src, node::Smoothstep::ID_A),
			{ dst, sw::node::Smoothstep::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Smoothstep::ID_B),
			{ dst, sw::node::Smoothstep::ID_B }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Smoothstep::ID_T),
			{ dst, sw::node::Smoothstep::ID_T }
		);
	}
	else if (id == bp::GetNodeTypeID<node::MatrixConstruction>())
	{
		auto& src = static_cast<const node::MatrixConstruction&>(node);
		dst = std::make_shared<sw::node::MatrixConstruction>(src.IsRow());
		sw::make_connecting(
			CreateInputChild(src, node::MatrixConstruction::ID_M0),
			{ dst, sw::node::MatrixConstruction::ID_M0 }
		);
		sw::make_connecting(
			CreateInputChild(src, node::MatrixConstruction::ID_M1),
			{ dst, sw::node::MatrixConstruction::ID_M1 }
		);
		sw::make_connecting(
			CreateInputChild(src, node::MatrixConstruction::ID_M2),
			{ dst, sw::node::MatrixConstruction::ID_M2 }
		);
		sw::make_connecting(
			CreateInputChild(src, node::MatrixConstruction::ID_M3),
			{ dst, sw::node::MatrixConstruction::ID_M3 }
		);
	}
	else if (id == bp::GetNodeTypeID<node::MatrixDeterminant>())
	{
		auto& src = static_cast<const node::MatrixDeterminant&>(node);
		dst = std::make_shared<sw::node::MatrixDeterminant>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::MatrixSplit>())
	{
		auto& src = static_cast<const node::MatrixSplit&>(node);
		dst = std::make_shared<sw::node::MatrixSplit>(src.IsRow());
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::MatrixTranspose>())
	{
		auto& src = static_cast<const node::MatrixTranspose&>(node);
		dst = std::make_shared<sw::node::MatrixTranspose>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Clamp>())
	{
		auto& src = static_cast<const node::Clamp&>(node);
		dst = std::make_shared<sw::node::Clamp>();
		sw::make_connecting(
			CreateInputChild(src, node::Clamp::ID_IN),
			{ dst, sw::node::Clamp::ID_IN }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Clamp::ID_MIN),
			{ dst, sw::node::Clamp::ID_MIN }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Clamp::ID_MAX),
			{ dst, sw::node::Clamp::ID_MAX }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Fraction>())
	{
		auto& src = static_cast<const node::Fraction&>(node);
		dst = std::make_shared<sw::node::Fraction>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Maximum>())
	{
		auto& src = static_cast<const node::Maximum&>(node);
		dst = std::make_shared<sw::node::Maximum>();
		sw::make_connecting(
			CreateInputChild(src, node::Maximum::ID_A),
			{ dst, sw::node::Maximum::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Maximum::ID_B),
			{ dst, sw::node::Maximum::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Minimum>())
	{
		auto& src = static_cast<const node::Minimum&>(node);
		dst = std::make_shared<sw::node::Minimum>();
		sw::make_connecting(
			CreateInputChild(src, node::Minimum::ID_A),
			{ dst, sw::node::Minimum::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Minimum::ID_B),
			{ dst, sw::node::Minimum::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::OneMinus>())
	{
		auto& src = static_cast<const node::OneMinus&>(node);
		dst = std::make_shared<sw::node::OneMinus>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::RandomRange>())
	{
		auto& src = static_cast<const node::RandomRange&>(node);
		dst = std::make_shared<sw::node::RandomRange>();
		sw::make_connecting(
			CreateInputChild(src, node::RandomRange::ID_SEED),
			{ dst, sw::node::RandomRange::ID_SEED }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RandomRange::ID_MIN),
			{ dst, sw::node::RandomRange::ID_MIN }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RandomRange::ID_MAX),
			{ dst, sw::node::RandomRange::ID_MAX }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Remap>())
	{
		auto& src = static_cast<const node::Remap&>(node);
		dst = std::make_shared<sw::node::Remap>();
		sw::make_connecting(
			CreateInputChild(src, node::Remap::ID_IN),
			{ dst, sw::node::Remap::ID_IN }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Remap::ID_FROM),
			{ dst, sw::node::Remap::ID_FROM }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Remap::ID_TO),
			{ dst, sw::node::Remap::ID_TO }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Saturate>())
	{
		auto& src = static_cast<const node::Saturate&>(node);
		dst = std::make_shared<sw::node::Saturate>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Ceiling>())
	{
		auto& src = static_cast<const node::Ceiling&>(node);
		dst = std::make_shared<sw::node::Ceiling>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Floor>())
	{
		auto& src = static_cast<const node::Floor&>(node);
		dst = std::make_shared<sw::node::Floor>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Round>())
	{
		auto& src = static_cast<const node::Round&>(node);
		dst = std::make_shared<sw::node::Round>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Sign>())
	{
		auto& src = static_cast<const node::Sign&>(node);
		dst = std::make_shared<sw::node::Sign>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Step>())
	{
		auto& src = static_cast<const node::Step&>(node);
		dst = std::make_shared<sw::node::Step>();
		sw::make_connecting(
			CreateInputChild(src, node::Step::ID_INPUT),
			{ dst, sw::node::Step::ID_INPUT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Step::ID_EDGE),
			{ dst, sw::node::Step::ID_EDGE }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Truncate>())
	{
		auto& src = static_cast<const node::Truncate&>(node);
		dst = std::make_shared<sw::node::Truncate>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Arccosine>())
	{
		auto& src = static_cast<const node::Arccosine&>(node);
		dst = std::make_shared<sw::node::Arccosine>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Arcsine>())
	{
		auto& src = static_cast<const node::Arcsine&>(node);
		dst = std::make_shared<sw::node::Arcsine>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Arctangent>())
	{
		auto& src = static_cast<const node::Arctangent&>(node);
		dst = std::make_shared<sw::node::Arctangent>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Arctangent2>())
	{
		auto& src = static_cast<const node::Arctangent2&>(node);
		dst = std::make_shared<sw::node::Arctangent2>();
		sw::make_connecting(
			CreateInputChild(src, node::Arctangent2::ID_A),
			{ dst, sw::node::Arctangent2::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Arctangent2::ID_B),
			{ dst, sw::node::Arctangent2::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Cosine>())
	{
		auto& src = static_cast<const node::Cosine&>(node);
		dst = std::make_shared<sw::node::Cosine>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::DegreesToRadians>())
	{
		auto& src = static_cast<const node::DegreesToRadians&>(node);
		dst = std::make_shared<sw::node::DegreesToRadians>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::HyperbolicCosine>())
	{
		auto& src = static_cast<const node::HyperbolicCosine&>(node);
		dst = std::make_shared<sw::node::HyperbolicCosine>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::HyperbolicSine>())
	{
		auto& src = static_cast<const node::HyperbolicSine&>(node);
		dst = std::make_shared<sw::node::HyperbolicSine>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::HyperbolicTangent>())
	{
		auto& src = static_cast<const node::HyperbolicTangent&>(node);
		dst = std::make_shared<sw::node::HyperbolicTangent>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::RadiansToDegrees>())
	{
		auto& src = static_cast<const node::RadiansToDegrees&>(node);
		dst = std::make_shared<sw::node::RadiansToDegrees>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Sine>())
	{
		auto& src = static_cast<const node::Sine&>(node);
		dst = std::make_shared<sw::node::Sine>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Tangent>())
	{
		auto& src = static_cast<const node::Tangent&>(node);
		dst = std::make_shared<sw::node::Tangent>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::CrossProduct>())
	{
		auto& src = static_cast<const node::CrossProduct&>(node);
		dst = std::make_shared<sw::node::CrossProduct>();
		sw::make_connecting(
			CreateInputChild(src, node::CrossProduct::ID_A),
			{ dst, sw::node::CrossProduct::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::CrossProduct::ID_B),
			{ dst, sw::node::CrossProduct::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Distance>())
	{
		auto& src = static_cast<const node::Distance&>(node);
		dst = std::make_shared<sw::node::Distance>();
		sw::make_connecting(
			CreateInputChild(src, node::Distance::ID_A),
			{ dst, sw::node::Distance::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Distance::ID_B),
			{ dst, sw::node::Distance::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::DotProduct>())
	{
		auto& src = static_cast<const node::DotProduct&>(node);
		dst = std::make_shared<sw::node::DotProduct>();
		sw::make_connecting(
			CreateInputChild(src, node::DotProduct::ID_A),
			{ dst, sw::node::DotProduct::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::DotProduct::ID_B),
			{ dst, sw::node::DotProduct::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Projection>())
	{
		auto& src = static_cast<const node::Projection&>(node);
		dst = std::make_shared<sw::node::Projection>();
		sw::make_connecting(
			CreateInputChild(src, node::Projection::ID_A),
			{ dst, sw::node::Projection::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Projection::ID_B),
			{ dst, sw::node::Projection::ID_B }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Rejection>())
	{
		auto& src = static_cast<const node::Rejection&>(node);
		dst = std::make_shared<sw::node::Rejection>();
		sw::make_connecting(
			CreateInputChild(src, node::Rejection::ID_A),
			{ dst, sw::node::Rejection::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Rejection::ID_B),
			{ dst, sw::node::Rejection::ID_B }
		);
	}
	// procedural
	else if (id == bp::GetNodeTypeID<node::Checkerboard>())
	{
		auto& src = static_cast<const node::Checkerboard&>(node);
		dst = std::make_shared<sw::node::Checkerboard>();
		sw::make_connecting(
			CreateInputChild(src, node::Checkerboard::ID_UV),
			{ dst, sw::node::Checkerboard::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Checkerboard::ID_COLOR_A),
			{ dst, sw::node::Checkerboard::ID_COLOR_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Checkerboard::ID_COLOR_B),
			{ dst, sw::node::Checkerboard::ID_COLOR_B }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Checkerboard::ID_FREQUENCY),
			{ dst, sw::node::Checkerboard::ID_FREQUENCY }
		);
	}
	else if (id == bp::GetNodeTypeID<node::GradientNoise>())
	{
		auto& src = static_cast<const node::GradientNoise&>(node);
		dst = std::make_shared<sw::node::GradientNoise>();
		sw::make_connecting(
			CreateInputChild(src, node::GradientNoise::ID_UV),
			{ dst, sw::node::GradientNoise::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::GradientNoise::ID_SCALE),
			{ dst, sw::node::GradientNoise::ID_SCALE }
		);
	}
	else if (id == bp::GetNodeTypeID<node::SimpleNoise>())
	{
		auto& src = static_cast<const node::SimpleNoise&>(node);
		dst = std::make_shared<sw::node::SimpleNoise>();
		sw::make_connecting(
			CreateInputChild(src, node::SimpleNoise::ID_UV),
			{ dst, sw::node::SimpleNoise::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::SimpleNoise::ID_SCALE),
			{ dst, sw::node::SimpleNoise::ID_SCALE }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Voronoi>())
	{
		auto& src = static_cast<const node::Voronoi&>(node);
		dst = std::make_shared<sw::node::Voronoi>();
		sw::make_connecting(
			CreateInputChild(src, node::Voronoi::ID_UV),
			{ dst, sw::node::Voronoi::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Voronoi::ID_ANGLE_OFFSET),
			{ dst, sw::node::Voronoi::ID_ANGLE_OFFSET }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Voronoi::ID_CELL_DENSITY),
			{ dst, sw::node::Voronoi::ID_CELL_DENSITY }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Ellipse>())
	{
		auto& src = static_cast<const node::Ellipse&>(node);
		dst = std::make_shared<sw::node::Ellipse>();
		sw::make_connecting(
			CreateInputChild(src, node::Ellipse::ID_UV),
			{ dst, sw::node::Ellipse::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Ellipse::ID_WIDTH),
			{ dst, sw::node::Ellipse::ID_WIDTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Ellipse::ID_HEIGHT),
			{ dst, sw::node::Ellipse::ID_HEIGHT }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Polygon>())
	{
		auto& src = static_cast<const node::Polygon&>(node);
		dst = std::make_shared<sw::node::Polygon>();
		sw::make_connecting(
			CreateInputChild(src, node::Polygon::ID_UV),
			{ dst, sw::node::Polygon::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Polygon::ID_SIDES),
			{ dst, sw::node::Polygon::ID_SIDES }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Polygon::ID_WIDTH),
			{ dst, sw::node::Polygon::ID_WIDTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Polygon::ID_HEIGHT),
			{ dst, sw::node::Polygon::ID_HEIGHT }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Rectangle>())
	{
		auto& src = static_cast<const node::Rectangle&>(node);
		dst = std::make_shared<sw::node::Rectangle>();
		sw::make_connecting(
			CreateInputChild(src, node::Rectangle::ID_UV),
			{ dst, sw::node::Rectangle::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Rectangle::ID_WIDTH),
			{ dst, sw::node::Rectangle::ID_WIDTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Rectangle::ID_HEIGHT),
			{ dst, sw::node::Rectangle::ID_HEIGHT }
		);
	}
	else if (id == bp::GetNodeTypeID<node::RoundedRectangle>())
	{
		auto& src = static_cast<const node::RoundedRectangle&>(node);
		dst = std::make_shared<sw::node::RoundedRectangle>();
		sw::make_connecting(
			CreateInputChild(src, node::RoundedRectangle::ID_UV),
			{ dst, sw::node::RoundedRectangle::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RoundedRectangle::ID_WIDTH),
			{ dst, sw::node::RoundedRectangle::ID_WIDTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RoundedRectangle::ID_HEIGHT),
			{ dst, sw::node::RoundedRectangle::ID_HEIGHT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RoundedRectangle::ID_RADIUS),
			{ dst, sw::node::RoundedRectangle::ID_RADIUS }
		);
	}
	// utility
	else if (id == bp::GetNodeTypeID<node::Preview>())
	{
		auto& src = static_cast<const node::Preview&>(node);
		dst = std::make_shared<sw::node::Assign>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::And>())
	{
		auto& src = static_cast<const node::And&>(node);
		dst = std::make_shared<sw::node::And>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::And::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::And::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::Or>())
	{
		auto& src = static_cast<const node::Or&>(node);
		dst = std::make_shared<sw::node::Or>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, sw::node::Or::ID_A });
		sw::make_connecting(CreateInputChild(src, 1), { dst, sw::node::Or::ID_B });
	}
	else if (id == bp::GetNodeTypeID<node::Not>())
	{
		auto& src = static_cast<const node::Not&>(node);
		dst = std::make_shared<sw::node::Not>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	else if (id == bp::GetNodeTypeID<node::Branch>())
	{
		auto& src = static_cast<const node::Branch&>(node);
		dst = std::make_shared<sw::node::Branch>();
		sw::make_connecting(
			CreateInputChild(src, node::Branch::ID_PREDICATE),
			{ dst, sw::node::Branch::ID_PREDICATE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Branch::ID_TRUE),
			{ dst, sw::node::Branch::ID_TRUE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Branch::ID_FALSE),
			{ dst, sw::node::Branch::ID_FALSE }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Comparison>())
	{
		auto& src = static_cast<const node::Comparison&>(node);
		dst = std::make_shared<sw::node::Comparison>(
			static_cast<sw::node::Comparison::CmpType>(src.GetCmpType())
		);
		sw::make_connecting(
			CreateInputChild(src, node::Comparison::ID_A),
			{ dst, sw::node::Comparison::ID_A }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Comparison::ID_B),
			{ dst, sw::node::Comparison::ID_B }
		);
	}
	//else if (id == bp::GetNodeTypeID<node::Input>())
	//{
	//	auto& src = static_cast<const node::Input&>(node);
	//	uint32_t type = 0;
	//	switch (src.GetType())
	//	{
	//	case PINS_TEXTURE2D:
	//		type = sw::t_tex2d;
	//		break;
	//	case PINS_VECTOR2:
	//		type = sw::t_flt2;
	//		break;
	//	default:
	//		// todo
	//		assert(0);
	//	}
	//	dst = std::make_shared<sw::node::Input>(src.GetName(), type);
	//}
	// UV
	else if (id == bp::GetNodeTypeID<node::Flipbook>())
	{
		auto& src = static_cast<const node::Flipbook&>(node);
		dst = std::make_shared<sw::node::Flipbook>(src.GetInvert());
		sw::make_connecting(
			CreateInputChild(src, node::Flipbook::ID_UV),
			{ dst, sw::node::Flipbook::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Flipbook::ID_WIDTH),
			{ dst, sw::node::Flipbook::ID_WIDTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Flipbook::ID_HEIGHT),
			{ dst, sw::node::Flipbook::ID_HEIGHT }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Flipbook::ID_TILE),
			{ dst, sw::node::Flipbook::ID_TILE }
		);
	}
	else if (id == bp::GetNodeTypeID<node::PolarCoordinates>())
	{
		auto& src = static_cast<const node::PolarCoordinates&>(node);
		dst = std::make_shared<sw::node::PolarCoordinates>();
		sw::make_connecting(
			CreateInputChild(src, node::PolarCoordinates::ID_UV),
			{ dst, sw::node::PolarCoordinates::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::PolarCoordinates::ID_CENTER),
			{ dst, sw::node::PolarCoordinates::ID_CENTER }
		);
		sw::make_connecting(
			CreateInputChild(src, node::PolarCoordinates::ID_RADIAL_SCALE),
			{ dst, sw::node::PolarCoordinates::ID_RADIAL_SCALE }
		);
		sw::make_connecting(
			CreateInputChild(src, node::PolarCoordinates::ID_LENGTH_SCALE),
			{ dst, sw::node::PolarCoordinates::ID_LENGTH_SCALE }
		);
	}
	else if (id == bp::GetNodeTypeID<node::RadialShear>())
	{
		auto& src = static_cast<const node::RadialShear&>(node);
		dst = std::make_shared<sw::node::RadialShear>();
		sw::make_connecting(
			CreateInputChild(src, node::RadialShear::ID_UV),
			{ dst, sw::node::RadialShear::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RadialShear::ID_CENTER),
			{ dst, sw::node::RadialShear::ID_CENTER }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RadialShear::ID_STRENGTH),
			{ dst, sw::node::RadialShear::ID_STRENGTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::RadialShear::ID_OFFSET),
			{ dst, sw::node::RadialShear::ID_OFFSET }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Rotate>())
	{
		auto& src = static_cast<const node::Rotate&>(node);
		dst = std::make_shared<sw::node::Rotate>(src.IsRadians());
		sw::make_connecting(
			CreateInputChild(src, node::Rotate::ID_UV),
			{ dst, sw::node::Rotate::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Rotate::ID_CENTER),
			{ dst, sw::node::Rotate::ID_CENTER }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Rotate::ID_ROTATION),
			{ dst, sw::node::Rotate::ID_ROTATION }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Spherize>())
	{
		auto& src = static_cast<const node::Spherize&>(node);
		dst = std::make_shared<sw::node::Spherize>();
		sw::make_connecting(
			CreateInputChild(src, node::Spherize::ID_UV),
			{ dst, sw::node::Spherize::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Spherize::ID_CENTER),
			{ dst, sw::node::Spherize::ID_CENTER }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Spherize::ID_STRENGTH),
			{ dst, sw::node::Spherize::ID_STRENGTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Spherize::ID_OFFSET),
			{ dst, sw::node::Spherize::ID_OFFSET }
		);
	}
	else if (id == bp::GetNodeTypeID<node::TilingAndOffset>())
	{
		auto& src = static_cast<const node::TilingAndOffset&>(node);
		dst = std::make_shared<sw::node::TilingAndOffset>();
		sw::make_connecting(
			CreateInputChild(src, node::TilingAndOffset::ID_UV),
			{ dst, sw::node::TilingAndOffset::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::TilingAndOffset::ID_TILLING),
			{ dst, sw::node::TilingAndOffset::ID_TILLING }
		);
		sw::make_connecting(
			CreateInputChild(src, node::TilingAndOffset::ID_OFFSET),
			{ dst, sw::node::TilingAndOffset::ID_OFFSET }
		);
	}
	else if (id == bp::GetNodeTypeID<node::Twirl>())
	{
		auto& src = static_cast<const node::Twirl&>(node);
		dst = std::make_shared<sw::node::Twirl>();
		sw::make_connecting(
			CreateInputChild(src, node::Twirl::ID_UV),
			{ dst, sw::node::Twirl::ID_UV }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Twirl::ID_CENTER),
			{ dst, sw::node::Twirl::ID_CENTER }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Twirl::ID_STRENGTH),
			{ dst, sw::node::Twirl::ID_STRENGTH }
		);
		sw::make_connecting(
			CreateInputChild(src, node::Twirl::ID_OFFSET),
			{ dst, sw::node::Twirl::ID_OFFSET }
		);
	}
	else
	{
		assert(0);
	}

	if (dst) {
		m_cached_nodes.push_back(dst);
	}

	return dst;
}

sw::Node::PortAddr ShaderWeaver::CreateInputChild(const bp::Node& node, int input_idx)
{
	auto& to_port = node.GetAllInput()[input_idx];
	auto& conns = to_port->GetConnecting();
	assert(conns.size() == 1);
	auto& from_port = conns[0]->GetFrom();
	assert(from_port);

	auto ret_node = CreateWeaverNode(from_port->GetParent());
	int  ret_idx  = from_port->GetPosIdx();
	return sw::Node::PortAddr(ret_node, ret_idx);
}

pt0::Shader::Params ShaderWeaver::CreateShaderParams(const sw::Evaluator& vert, const sw::Evaluator& frag) const
{
	pt0::Shader::Params sp(m_texture_names, m_layout);
	sp.vs = vert.GetShaderStr().c_str();
	sp.fs = frag.GetShaderStr().c_str();
	// todo
	sp.uniform_names.model_mat  = "u_model";
	sp.uniform_names.view_mat   = "u_view";
	sp.uniform_names.proj_mat   = "u_projection";
	sp.uniform_names.time       = "u_time";
	sp.uniform_names.sine_time  = "u_sine_time";
	sp.uniform_names.cos_time   = "u_cos_time";
	sp.uniform_names.delta_time = "u_delta_time";
	return sp;
}

}