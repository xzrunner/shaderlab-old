#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/Pins.h"

// artistic
#include "shadergraph/node/Gray.h"
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

#include <blueprint/Node.h>
#include <blueprint/Pins.h>
#include <blueprint/Connecting.h>
#include <blueprint/CompNode.h>

#include <shaderweaver/Evaluator.h>
// artistic
#include <shaderweaver/node/Gray.h>
// input
#include <shaderweaver/node/Time.h>
#include <shaderweaver/node/Vector1.h>
#include <shaderweaver/node/Vector2.h>
#include <shaderweaver/node/Vector3.h>
#include <shaderweaver/node/Vector4.h>
#include <shaderweaver/node/UV.h>
#include <shaderweaver/node/SampleTex2D.h>
// master
#include <shaderweaver/node/Phong.h>
// math
#include <shaderweaver/node/Add.h>
#include <shaderweaver/node/Divide.h>
#include <shaderweaver/node/Multiply.h>
#include <shaderweaver/node/Subtract.h>
#include <shaderweaver/node/InverseLerp.h>
#include <shaderweaver/node/Lerp.h>
#include <shaderweaver/node/Remap.h>
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
// uv
#include <shaderweaver/node/Rotate.h>
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
	if (id == bp::GetNodeTypeID<node::Gray>())
	{
		auto& src = static_cast<const node::Gray&>(node);
		dst = std::make_shared<sw::node::Gray>();
		sw::make_connecting(CreateInputChild(src, 0), { dst, 0 });
	}
	// input
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