#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/Pins.h"
#include "shadergraph/RegistNodes.h"

#include <shaderweaver/node/Uniform.h>
#include <shaderweaver/node/Input.h>
#include <shaderweaver/node/Output.h>
#include <shaderweaver/node/PositionTrans.h>
#include <shaderweaver/node/FragPosTrans.h>
#include <shaderweaver/node/NormalTrans.h>
#include <shaderweaver/node/Phong.h>
#include <shaderweaver/node/Time.h>
#include <shaderweaver/node/Hue.h>
#include <shaderweaver/node/InvertColors.h>
#include <shaderweaver/node/Blend.h>
#include <shaderweaver/node/ChannelMask.h>
#include <shaderweaver/node/ColorspaceConversion.h>
#include <shaderweaver/node/Flip.h>
#include <shaderweaver/node/Swizzle.h>
#include <shaderweaver/node/Boolean.h>
#include <shaderweaver/node/Vector1.h>
#include <shaderweaver/node/Vector2.h>
#include <shaderweaver/node/Vector3.h>
#include <shaderweaver/node/Vector4.h>
#include <shaderweaver/node/UV.h>
#include <shaderweaver/node/Matrix2.h>
#include <shaderweaver/node/Matrix3.h>
#include <shaderweaver/node/Matrix4.h>
#include <shaderweaver/node/Exponential.h>
#include <shaderweaver/node/Log.h>
#include <shaderweaver/node/MatrixConstruction.h>
#include <shaderweaver/node/MatrixSplit.h>
#include <shaderweaver/node/Comparison.h>
#include <shaderweaver/node/Flipbook.h>
#include <shaderweaver/node/Rotate.h>
#include <shaderweaver/node/Raymarching.h>

#include <blueprint/Node.h>
#include <blueprint/Pins.h>
#include <blueprint/Connecting.h>
#include <blueprint/CompNode.h>
#include <shaderweaver/Evaluator.h>
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
	printf("%s\n", vert.GenShaderStr().c_str());
	printf("//////////////////////////////////////////////////////////////////////////\n");
	printf("%s\n", frag.GenShaderStr().c_str());
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

ShaderWeaver::ShaderWeaver(ShaderType shader_type, const bp::Node& frag_node, bool debug_print)
	: m_debug_print(debug_print)
{
	switch (shader_type)
	{
	case SHADER_SHAPE:
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
	case SHADER_SPRITE:
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
	case SHADER_PHONG:
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
	case SHADER_RAYMARCHING:
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
		m_cached_nodes.push_back(position);

		auto pos_trans = std::make_shared<sw::node::PositionTrans>(3);
		sw::make_connecting({ projection, 0 }, { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },       { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },      { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 },   { pos_trans, sw::node::PositionTrans::ID_POS });
		m_vert_nodes.push_back(pos_trans);

		add_vert_varying(m_vert_nodes, m_cached_nodes, "texcoord", sw::t_uv);

		// frag
		auto raymarching = CreateWeaverNode(frag_node);
		m_frag_node = raymarching;
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
	// create node
	sw::NodePtr dst = nullptr;
	auto type = node.get_type();
	auto cls_name = type.get_name().to_string();
	if (cls_name == "sg::Tex2DAsset")
	{
		dst = std::make_shared<sw::node::Uniform>(node.GetName(), sw::t_tex2d);
	}
	else
	{
		cls_name = "sw::" + cls_name.substr(cls_name.find("sg::") + strlen("sg::"));

		rttr::type t = rttr::type::get_by_name(cls_name);
		if (!t.is_valid()) {
			return nullptr;
		}
		assert(t.is_valid());
		rttr::variant var = t.create();
		assert(var.is_valid());

		dst = var.get_value<std::shared_ptr<sw::Node>>();
		assert(dst);
	}

	// connect
	for (int i = 0, n = node.GetAllInput().size(); i < n; ++i)
	{
		auto& imports = dst->GetImports();
		if (!imports[i].var.IsDefaultInput()) {
			continue;
		}
		auto from = CreateInputChild(node, i);
		if (from.node.expired()) {
			continue;
		}
		sw::make_connecting(from, { dst, i });
	}

	// init
	if (type == rttr::type::get<node::Hue>())
	{
		auto& src = static_cast<const node::Hue&>(node);
		std::static_pointer_cast<sw::node::Hue>(dst)->
			SetRadians(src.GetAngleType() == PropAngleType::RADIAN);
	}
	else if (type == rttr::type::get<node::InvertColors>())
	{
		auto& src = static_cast<const node::InvertColors&>(node);
		std::static_pointer_cast<sw::node::InvertColors>(dst)->
			SetChannels(src.GetChannels().channels);
	}
	else if (type == rttr::type::get<node::Blend>())
	{
		auto& src = static_cast<const node::Blend&>(node);
		std::static_pointer_cast<sw::node::Blend>(dst)->
			SetModeType(static_cast<sw::node::Blend::ModeType>(src.GetMode()));
	}
	else if (type == rttr::type::get<node::ChannelMask>())
	{
		auto& src = static_cast<const node::ChannelMask&>(node);
		std::static_pointer_cast<sw::node::ChannelMask>(dst)->
			SetChannels(src.GetChannels().channels);
	}
	else if (type == rttr::type::get<node::ColorspaceConversion>())
	{
		auto& src = static_cast<const node::ColorspaceConversion&>(node);
		auto from = static_cast<sw::node::ColorspaceConversion::ColorType>(src.GetType().from);
		auto to = static_cast<sw::node::ColorspaceConversion::ColorType>(src.GetType().to);
		std::static_pointer_cast<sw::node::ColorspaceConversion>(dst)->SetColType(from, to);
	}
	else if (type == rttr::type::get<node::Flip>())
	{
		auto& src = static_cast<const node::Flip&>(node);
		std::static_pointer_cast<sw::node::Flip>(dst)->SetChannels(src.GetChannels().channels);
	}
	else if (type == rttr::type::get<node::Swizzle>())
	{
		auto& src = static_cast<const node::Swizzle&>(node);
		auto& src_channels = src.GetChannels().channels;
		std::array<sw::node::Swizzle::ChannelType, sw::node::Swizzle::CHANNEL_COUNT> dst_channels;
		for (size_t i = 0; i < sw::node::Swizzle::CHANNEL_COUNT; ++i) {
			dst_channels[i] = static_cast<sw::node::Swizzle::ChannelType>(src_channels[i]);
		}
		std::static_pointer_cast<sw::node::Swizzle>(dst)->SetChannels(dst_channels);
	}
	else if (type == rttr::type::get<node::Boolean>())
	{
		auto& src = static_cast<const node::Boolean&>(node);
		auto boolean = std::static_pointer_cast<sw::node::Boolean>(dst);
		boolean->SetName(src.GetName());
		boolean->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Vector1>())
	{
		auto& src = static_cast<const node::Vector1&>(node);
		auto vec1 = std::static_pointer_cast<sw::node::Vector1>(dst);
		vec1->SetName(src.GetName());
		vec1->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Vector2>())
	{
		auto& src = static_cast<const node::Vector2&>(node);
		auto vec2 = std::static_pointer_cast<sw::node::Vector2>(dst);
		vec2->SetName(src.GetName());
		vec2->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Vector3>())
	{
		auto& src = static_cast<const node::Vector3&>(node);
		auto vec3 = std::static_pointer_cast<sw::node::Vector3>(dst);
		vec3->SetName(src.GetName());
		vec3->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Vector4>())
	{
		auto& src = static_cast<const node::Vector4&>(node);
		auto vec4 = std::static_pointer_cast<sw::node::Vector4>(dst);
		vec4->SetName(src.GetName());
		vec4->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::UV>())
	{
		auto& src = static_cast<const node::UV&>(node);
		std::static_pointer_cast<sw::node::UV>(dst)->SetName(src.GetName());
	}
	else if (type == rttr::type::get<node::Matrix2>())
	{
		auto& src = static_cast<const node::Matrix2&>(node);
		auto mat2 = std::static_pointer_cast<sw::node::Matrix2>(dst);
		mat2->SetName(src.GetName());
		mat2->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Matrix3>())
	{
		auto& src = static_cast<const node::Matrix3&>(node);
		auto mat3 = std::static_pointer_cast<sw::node::Matrix3>(dst);
		mat3->SetName(src.GetName());
		mat3->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Matrix4>())
	{
		auto& src = static_cast<const node::Matrix4&>(node);
		auto mat4 = std::static_pointer_cast<sw::node::Matrix4>(dst);
		mat4->SetName(src.GetName());
		mat4->SetValue(src.GetValue());
	}
	else if (type == rttr::type::get<node::Tex2DAsset>())
	{
		auto& src = static_cast<const node::Tex2DAsset&>(node);
		m_texture_names.push_back(src.GetName());
		auto& img = src.GetImage();
		if (img) {
			m_texture_ids.push_back(img->GetTexID());
		}
		std::static_pointer_cast<sw::node::Uniform>(dst)->
			SetNameAndType(src.GetName(), sw::t_tex2d);
	}
	else if (type == rttr::type::get<node::Exponential>())
	{
		auto& src = static_cast<const node::Exponential&>(node);
		std::static_pointer_cast<sw::node::Exponential>(dst)->
			SetType(static_cast<sw::node::Exponential::BaseType>(src.GetType()));
	}
	else if (type == rttr::type::get<node::Log>())
	{
		auto& src = static_cast<const node::Log&>(node);
		std::static_pointer_cast<sw::node::Log>(dst)->
			SetType(static_cast<sw::node::Log::BaseType>(src.GetType()));
	}
	else if (type == rttr::type::get<node::MatrixConstruction>())
	{
		auto& src = static_cast<const node::MatrixConstruction&>(node);
		std::static_pointer_cast<sw::node::MatrixConstruction>(dst)->
			SetRow(src.GetType() == MatrixType::ROW);
	}
	else if (type == rttr::type::get<node::MatrixSplit>())
	{
		auto& src = static_cast<const node::MatrixSplit&>(node);
		std::static_pointer_cast<sw::node::MatrixSplit>(dst)->
			SetRow(src.GetType() == MatrixType::ROW);
	}
	else if (type == rttr::type::get<node::Comparison>())
	{
		auto& src = static_cast<const node::Comparison&>(node);
		std::static_pointer_cast<sw::node::Comparison>(dst)->
			SetCmpType(static_cast<sw::node::Comparison::CmpType>(src.GetType()));
	}
	else if (type == rttr::type::get<node::Flipbook>())
	{
		auto& src = static_cast<const node::Flipbook&>(node);
		std::static_pointer_cast<sw::node::Flipbook>(dst)->
			SetInvert(src.GetInvert());
	}
	else if (type == rttr::type::get<node::Rotate>())
	{
		auto& src = static_cast<const node::Rotate&>(node);
		std::static_pointer_cast<sw::node::Rotate>(dst)->
			SetRadians(src.GetAngleType() == PropAngleType::RADIAN);
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
	sp.vs = vert.GenShaderStr().c_str();
	sp.fs = frag.GenShaderStr().c_str();

	sp.uniform_names.model_mat  = "u_model";
	sp.uniform_names.view_mat   = "u_view";
	sp.uniform_names.proj_mat   = "u_projection";

	if (vert.HasNodeType<sw::node::Time>() || frag.HasNodeType<sw::node::Time>()) {
		sp.utime_names = std::make_unique<pt0::Shader::UniformTimeNames>(
			pt0::Shader::UniformTimeNames{
                sw::node::Time::TimeName(),
                sw::node::Time::SineTimeName(),
                sw::node::Time::CosTimeName(),
                sw::node::Time::DeltaTimeName()
            }
		);
	}

    if (vert.HasNodeType<sw::node::Raymarching>() || frag.HasNodeType<sw::node::Raymarching>()) {
        sp.uniform_names.resolution = sw::node::Raymarching::ResolutionName();
    }

	return sp;
}

}