#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/RegistNodes.h"
#include "shadergraph/node/Custom.h"

#include <shaderweaver/node/Uniform.h>
#include <shaderweaver/node/Input.h>
#include <shaderweaver/node/Output.h>
#include <shaderweaver/node/PositionTrans.h>
#include <shaderweaver/node/FragPosTrans.h>
#include <shaderweaver/node/NormalTrans.h>
#include <shaderweaver/node/PBR.h>
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
#include <shaderweaver/node/CameraPos.h>
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
#include <shaderweaver/node/Custom.h>
#include <shaderweaver/node/VertexShader.h>
#include <shaderweaver/node/FragmentShader.h>

#include <blueprint/Node.h>
#include <blueprint/Pins.h>
#include <blueprint/Connecting.h>
#include <blueprint/CompNode.h>
#include <blueprint/node/GetLocalVar.h>
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

const char* PROJ_MAT_NAME  = "u_projection";
const char* VIEW_MAT_NAME  = "u_view";
const char* MODEL_MAT_NAME = "u_model";

const char* VERT_POSITION_NAME  = "position";
const char* VERT_NORMAL_NAME    = "normal";
const char* VERT_TEXCOORD_NAME  = "texcoord";

const char* FRAG_POSITION_NAME = "v_world_pos";
const char* FRAG_NORMAL_NAME   = "v_normal";
const char* FRAG_TEXCOORD_NAME = "v_texcoord";

void debug_print(const sw::Evaluator& vert, const sw::Evaluator& frag)
{
	printf("//////////////////////////////////////////////////////////////////////////\n");
	printf("%s\n", vert.GenShaderStr().c_str());
	printf("//////////////////////////////////////////////////////////////////////////\n");
	printf("%s\n", frag.GenShaderStr().c_str());
	printf("//////////////////////////////////////////////////////////////////////////\n");
}

uint32_t var_type_sg_to_sw(int type)
{
    uint32_t ret = 0;
    switch (type)
    {
    case sg::PINS_BOOLEAN:
        ret = sw::t_bool;
        break;
    case sg::PINS_DYNAMIC_VECTOR:
        ret = sw::t_d_vec;
        break;
    case sg::PINS_VECTOR1:
        ret = sw::t_flt1;
        break;
    case sg::PINS_VECTOR2:
        ret = sw::t_flt2;
        break;
    case sg::PINS_VECTOR3:
        ret = sw::t_flt3;
        break;
    case sg::PINS_VECTOR4:
        ret = sw::t_flt4;
        break;
    case sg::PINS_COLOR:
        ret = sw::t_col3;
        break;
    case sg::PINS_TEXTURE2D:
        ret = sw::t_tex2d;
        break;
    case sg::PINS_CUBE_MAP:
        break;
    case sg::PINS_DYNAMIC_MATRIX:
        ret = sw::t_d_mat;
        break;
    case sg::PINS_MATRIX2:
        ret = sw::t_mat2;
        break;
    case sg::PINS_MATRIX3:
        ret = sw::t_mat3;
        break;
    case sg::PINS_MATRIX4:
        ret = sw::t_mat4;
        break;
    case sg::PINS_FUNCTION:
        ret = sw::t_func;
        break;
    }
    return ret;
}

/*
    v_texcoord = a_tex_coords;
    v_world_pos = vec3(u_model * a_pos);
    v_normal = mat3(u_model) * a_normal;

    gl_Position =  u_projection * u_view * u_model * a_pos;
*/
void init_vert3d(std::vector<sw::NodePtr>& m_cached_nodes, std::vector<sw::NodePtr>& m_vert_nodes)
{
	auto projection = std::make_shared<sw::node::Uniform>(PROJ_MAT_NAME,  sw::t_mat4);
	auto view       = std::make_shared<sw::node::Uniform>(VIEW_MAT_NAME,  sw::t_mat4);
	auto model      = std::make_shared<sw::node::Uniform>(MODEL_MAT_NAME, sw::t_mat4);
	m_cached_nodes.push_back(projection);
	m_cached_nodes.push_back(view);
	m_cached_nodes.push_back(model);

	auto position = std::make_shared<sw::node::Input>(VERT_POSITION_NAME, sw::t_flt3);
	auto normal   = std::make_shared<sw::node::Input>(VERT_NORMAL_NAME,   sw::t_nor3);
    auto texcoord = std::make_shared<sw::node::Input>(VERT_TEXCOORD_NAME, sw::t_uv);
	m_cached_nodes.push_back(position);
	m_cached_nodes.push_back(normal);
    m_cached_nodes.push_back(texcoord);

    // gl_Position =  u_projection * u_view * u_model * a_pos;
	auto pos_trans = std::make_shared<sw::node::PositionTrans>(4);
	sw::make_connecting({ projection, 0 }, { pos_trans, sw::node::PositionTrans::ID_PROJ });
	sw::make_connecting({ view, 0 },       { pos_trans, sw::node::PositionTrans::ID_VIEW });
	sw::make_connecting({ model, 0 },      { pos_trans, sw::node::PositionTrans::ID_MODEL });
	sw::make_connecting({ position, 0 },   { pos_trans, sw::node::PositionTrans::ID_POS });
    m_cached_nodes.push_back(pos_trans);
    auto vert_end = std::make_shared<sw::node::VertexShader>();
    sw::make_connecting({ pos_trans, 0 }, { vert_end, 0 });
    m_vert_nodes.push_back(vert_end);

	auto frag_pos_trans = std::make_shared<sw::node::FragPosTrans>();
	sw::make_connecting({ model, 0 },    { frag_pos_trans, sw::node::FragPosTrans::ID_MODEL });
	sw::make_connecting({ position, 0 }, { frag_pos_trans, sw::node::FragPosTrans::ID_POS });
    m_cached_nodes.push_back(frag_pos_trans);

    auto normal_mat = std::make_shared<sw::node::Uniform>(sw::node::NormalTrans::NormalMatName(), sw::t_mat3);
    m_cached_nodes.push_back(normal_mat);
	auto norm_trans = std::make_shared<sw::node::NormalTrans>();
	sw::make_connecting({ normal_mat, 0 }, { norm_trans, sw::node::NormalTrans::ID_NORMAL_MAT });
	sw::make_connecting({ normal, 0 },     { norm_trans, sw::node::NormalTrans::ID_NORMAL });
    m_cached_nodes.push_back(norm_trans);

    // v_texcoord = a_texcoord;
    auto v_texcoord = std::make_shared<sw::node::Output>(FRAG_TEXCOORD_NAME, sw::t_uv);
    sw::make_connecting({ texcoord, 0 }, { v_texcoord, 0 });
    m_vert_nodes.push_back(v_texcoord);

    // v_world_pos = vec3(u_model * a_pos);
    auto v_world_pos = std::make_shared<sw::node::Output>(FRAG_POSITION_NAME, sw::t_flt3);
    sw::make_connecting({ frag_pos_trans, 0 }, { v_world_pos, 0 });
    m_vert_nodes.push_back(v_world_pos);

    // v_normal = mat3(transpose(inverse(u_model))) * a_normal;
    auto v_normal = std::make_shared<sw::node::Output>(FRAG_NORMAL_NAME, sw::t_nor3);
    sw::make_connecting({ norm_trans, 0 }, { v_normal, 0 });
    m_vert_nodes.push_back(v_normal);
}

}

namespace sg
{

ShaderWeaver::ShaderWeaver(ShaderType shader_type, const bp::Node& frag_node,
                           bool debug_print, const std::vector<bp::NodePtr>& all_nodes)
	: m_debug_print(debug_print)
{
    sw::NodePtr frag_end = nullptr;

	// prepare m_map2setnodes
    for (auto& n : all_nodes) {
        if (n->get_type() == rttr::type::get<bp::node::SetLocalVar>()) {
            auto set_node = std::static_pointer_cast<const bp::node::SetLocalVar>(n);
            m_map2setnodes.insert({ set_node->GetVarName(), set_node });
        }
    }

    switch (shader_type)
	{
	case SHADER_SHAPE:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib(VERT_POSITION_NAME, 2, 4, 8, 0));

		// vert

		auto proj  = std::make_shared<sw::node::Uniform>(PROJ_MAT_NAME,  sw::t_mat4);
		auto view  = std::make_shared<sw::node::Uniform>(VIEW_MAT_NAME,  sw::t_mat4);
		auto model = std::make_shared<sw::node::Uniform>(MODEL_MAT_NAME, sw::t_mat4);
		m_cached_nodes.push_back(proj);
		m_cached_nodes.push_back(view);
		m_cached_nodes.push_back(model);

		auto position = std::make_shared<sw::node::Input>(VERT_POSITION_NAME, sw::t_pos2);
		m_cached_nodes.push_back(position);

		auto pos_trans = std::make_shared<sw::node::PositionTrans>(2);
		sw::make_connecting({ proj, 0 },     { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },     { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },    { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 }, { pos_trans, sw::node::PositionTrans::ID_POS });
        m_cached_nodes.push_back(pos_trans);
        auto vert_end = std::make_shared<sw::node::VertexShader>();
        sw::make_connecting({ pos_trans, 0 }, { vert_end, 0 });
		m_vert_nodes.push_back(vert_end);

        frag_end = CreateWeaverNode(frag_node);
	}
		break;
	case SHADER_SPRITE:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib(VERT_POSITION_NAME, 2, 4, 16, 0));
		m_layout.push_back(ur::VertexAttrib(VERT_TEXCOORD_NAME, 2, 4, 16, 8));

		// vert

		auto proj  = std::make_shared<sw::node::Uniform>(PROJ_MAT_NAME,  sw::t_mat4);
		auto view  = std::make_shared<sw::node::Uniform>(VIEW_MAT_NAME,  sw::t_mat4);
		auto model = std::make_shared<sw::node::Uniform>(MODEL_MAT_NAME, sw::t_mat4);
		m_cached_nodes.push_back(proj);
		m_cached_nodes.push_back(view);
		m_cached_nodes.push_back(model);

		auto position = std::make_shared<sw::node::Input>(VERT_POSITION_NAME, sw::t_pos2);
		m_cached_nodes.push_back(position);

        // gl_Position =  u_projection * u_view * u_model * a_pos;
		auto pos_trans = std::make_shared<sw::node::PositionTrans>(2);
		sw::make_connecting({ proj, 0 },     { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },     { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },    { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 }, { pos_trans, sw::node::PositionTrans::ID_POS });
        m_cached_nodes.push_back(pos_trans);
        auto vert_end = std::make_shared<sw::node::VertexShader>();
        sw::make_connecting({ pos_trans, 0 }, { vert_end, 0 });
        m_vert_nodes.push_back(vert_end);

        // v_texcoord = a_texcoord;
        auto a_texcoord = std::make_shared<sw::node::Input>(VERT_TEXCOORD_NAME, sw::t_uv);
        auto v_texcoord = std::make_shared<sw::node::Output>(FRAG_TEXCOORD_NAME, sw::t_uv);
        sw::make_connecting({ a_texcoord, 0 }, { v_texcoord, 0 });
        m_vert_nodes.push_back(v_texcoord);
        m_cached_nodes.push_back(a_texcoord);

		// frag
		frag_end = CreateWeaverNode(frag_node);
        // fixme
        if (frag_end->get_type() == rttr::type::get<sw::node::Raymarching>()) {
            auto cam_pos = std::make_shared<sw::node::CameraPos>();
            m_cached_nodes.push_back(cam_pos);
            sw::make_connecting({ cam_pos, 0 }, { frag_end, sw::node::Raymarching::ID_CAM_POS });
        }
	}
		break;
	case SHADER_PHONG:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib(VERT_POSITION_NAME, 3, 4, 32, 0));
		m_layout.push_back(ur::VertexAttrib(VERT_NORMAL_NAME,   3, 4, 32, 12));
		m_layout.push_back(ur::VertexAttrib(VERT_TEXCOORD_NAME, 2, 4, 32, 24));

		// vert
        init_vert3d(m_cached_nodes, m_vert_nodes);

		// frag
		auto phong = CreateWeaverNode(frag_node);

        auto cam_pos = std::make_shared<sw::node::CameraPos>();
		auto frag_in_pos = std::make_shared<sw::node::Input>(FRAG_POSITION_NAME, sw::t_flt3);
		auto frag_in_nor = std::make_shared<sw::node::Input>(FRAG_NORMAL_NAME, sw::t_nor3);
        m_cached_nodes.push_back(cam_pos);
		m_cached_nodes.push_back(frag_in_pos);
		m_cached_nodes.push_back(frag_in_nor);
        sw::make_connecting({ cam_pos, 0 }, { phong, sw::node::Phong::ID_VIEW_POS });
		sw::make_connecting({ frag_in_pos, 0 }, { phong, sw::node::Phong::ID_FRAG_POS });
		sw::make_connecting({ frag_in_nor, 0 }, { phong, sw::node::Phong::ID_NORMAL });

		frag_end = phong;
	}
		break;
    case SHADER_PBR:
    {
		// layout
		m_layout.push_back(ur::VertexAttrib(VERT_POSITION_NAME, 3, 4, 32, 0));
		m_layout.push_back(ur::VertexAttrib(VERT_NORMAL_NAME,   3, 4, 32, 12));
		m_layout.push_back(ur::VertexAttrib(VERT_TEXCOORD_NAME, 2, 4, 32, 24));

        // vert
        init_vert3d(m_cached_nodes, m_vert_nodes);

        // frag
        auto pbr = CreateWeaverNode(frag_node);

        auto frag_in_pos = std::make_shared<sw::node::Input>(FRAG_POSITION_NAME, sw::t_flt3);
        auto frag_in_nor = std::make_shared<sw::node::Input>(FRAG_NORMAL_NAME,    sw::t_nor3);
        auto frag_in_tex = std::make_shared<sw::node::Input>(FRAG_TEXCOORD_NAME,  sw::t_uv);
        auto cam_pos = std::make_shared<sw::node::CameraPos>();
        m_cached_nodes.push_back(frag_in_pos);
        m_cached_nodes.push_back(frag_in_nor);
        m_cached_nodes.push_back(frag_in_tex);
        m_cached_nodes.push_back(cam_pos);
        sw::make_connecting({ frag_in_pos, 0 }, { pbr, sw::node::PBR::ID_FRAG_POS });
        sw::make_connecting({ frag_in_nor, 0 }, { pbr, sw::node::PBR::ID_NORMAL });
        sw::make_connecting({ frag_in_tex, 0 }, { pbr, sw::node::PBR::ID_TEXCOORD });
        sw::make_connecting({ cam_pos, 0 }, { pbr, sw::node::PBR::ID_CAM_POS });

        frag_end = pbr;
    }
        break;
	case SHADER_RAYMARCHING:
	{
		// layout
		m_layout.push_back(ur::VertexAttrib(VERT_POSITION_NAME, 3, 4, 32, 0));

		// vert
		auto projection = std::make_shared<sw::node::Uniform>(PROJ_MAT_NAME,  sw::t_mat4);
		auto view       = std::make_shared<sw::node::Uniform>(VIEW_MAT_NAME,  sw::t_mat4);
		auto model      = std::make_shared<sw::node::Uniform>(MODEL_MAT_NAME, sw::t_mat4);
		m_cached_nodes.push_back(projection);
		m_cached_nodes.push_back(view);
		m_cached_nodes.push_back(model);

		auto position = std::make_shared<sw::node::Input>(VERT_POSITION_NAME, sw::t_flt3);
		m_cached_nodes.push_back(position);

		auto pos_trans = std::make_shared<sw::node::PositionTrans>(4);
		sw::make_connecting({ projection, 0 }, { pos_trans, sw::node::PositionTrans::ID_PROJ });
		sw::make_connecting({ view, 0 },       { pos_trans, sw::node::PositionTrans::ID_VIEW });
		sw::make_connecting({ model, 0 },      { pos_trans, sw::node::PositionTrans::ID_MODEL });
		sw::make_connecting({ position, 0 },   { pos_trans, sw::node::PositionTrans::ID_POS });
        m_cached_nodes.push_back(pos_trans);
        auto vert_end = std::make_shared<sw::node::VertexShader>();
        sw::make_connecting({ pos_trans, 0 }, { vert_end, 0 });
		m_vert_nodes.push_back(vert_end);

		// frag
		auto raymarching = CreateWeaverNode(frag_node);

        auto cam_pos = std::make_shared<sw::node::CameraPos>();
        m_cached_nodes.push_back(cam_pos);
        sw::make_connecting({ cam_pos, 0 }, { raymarching, sw::node::Raymarching::ID_CAM_POS });

		frag_end = raymarching;
	}
		break;
	default:
		assert(0);
	}

    m_frag_node = std::make_shared<sw::node::FragmentShader>();
    sw::make_connecting({ frag_end, 0 }, { m_frag_node, 0 });
}

std::shared_ptr<pt2::Shader> ShaderWeaver::CreateShader2() const
{
	sw::Evaluator vert(m_vert_nodes);
	sw::Evaluator frag({ m_frag_node });

	if (m_debug_print) {
		debug_print(vert, frag);
	}

	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	auto shader = std::make_shared<pt2::Shader>(&rc, CreateShaderParams(vert, frag));

	shader->SetUsedTextures(m_texture_ids);

	return shader;
}

std::shared_ptr<pt3::Shader> ShaderWeaver::CreateShader3() const
{
	sw::Evaluator vert(m_vert_nodes);
	sw::Evaluator frag({ m_frag_node });

	if (m_debug_print) {
		debug_print(vert, frag);
	}

	auto& rc = ur::Blackboard::Instance()->GetRenderContext();
	auto shader = std::make_shared<pt3::Shader>(&rc, CreateShaderParams(vert, frag));

	shader->SetUsedTextures(m_texture_ids);

	return shader;
}

sw::NodePtr ShaderWeaver::CreateWeaverNode(const bp::Node& node)
{
	// create node
	sw::NodePtr dst = nullptr;
	auto type = node.get_type();
    if (type == rttr::type::get<bp::node::GetLocalVar>())
    {
        auto& get_node = static_cast<const bp::node::GetLocalVar&>(node);
        auto itr = m_map2setnodes.find(get_node.GetVarName());
        if (itr != m_map2setnodes.end()) {
            auto& conns = itr->second->GetAllInput()[0]->GetConnecting();
            if (!conns.empty()) {
                assert(conns.size() == 1);
                auto& bp_from_port = conns[0]->GetFrom();
                assert(bp_from_port);
                return CreateWeaverNode(bp_from_port->GetParent());
            }
        }
    }
	else if (type == rttr::type::get<sg::node::Tex2DAsset>())
	{
        auto& tex2d = static_cast<const sg::node::Tex2DAsset&>(node);
		dst = std::make_shared<sw::node::Uniform>(tex2d.GetName(), sw::t_tex2d);
	}
	else
	{
        auto cls_name = type.get_name().to_string();
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

    if (!dst) {
        return nullptr;
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
    else if (type == rttr::type::get<node::Custom>())
    {
        auto& src = static_cast<const node::Custom&>(node);
        auto cus = std::static_pointer_cast<sw::node::Custom>(dst);

        std::vector<sw::Variable> params;
        auto& inputs = src.GetAllInput();
        params.reserve(inputs.size());
        for (auto& i : inputs) {
            sw::Variable var(var_type_sg_to_sw(i->GetType()), i->GetName());
            params.push_back(var);
        }
        cus->SetParams(params);

        auto& outputs = src.GetAllOutput();
        if (!outputs.empty())
        {
            sw::Variable ret(var_type_sg_to_sw(outputs[0]->GetType()), outputs[0]->GetName());
            cus->SetReturn(ret);
        }

        cus->SetName(src.GetName());
        cus->SetHeadStr(src.GetHeadStr());
        cus->SetBodyStr(src.GetBodyStr());
    }

    // connect
    for (int i = 0, n = node.GetAllInput().size(); i < n; ++i)
    {
        auto& imports = dst->GetImports();
        if (!imports[i].var.IsDefaultInput()) {
            continue;
        }
        sw::Node::PortAddr from_port;
        if (!CreateFromNode(node, i, from_port) ||
            from_port.node.expired()) {
            continue;
        }
        sw::make_connecting(from_port, { dst, i });
    }

    m_cached_nodes.push_back(dst);

	return dst;
}

bool ShaderWeaver::CreateFromNode(const bp::Node& node, int input_idx, sw::Node::PortAddr& from_port)
{
    auto& to_port = node.GetAllInput()[input_idx];
    auto& conns = to_port->GetConnecting();
    if (conns.empty()) {
        return false;
    }
    assert(conns.size() == 1);
    auto& bp_from_port = conns[0]->GetFrom();
    assert(bp_from_port);

    from_port.node = CreateWeaverNode(bp_from_port->GetParent());
    from_port.idx  = bp_from_port->GetPosIdx();
    return true;
}

pt0::Shader::Params ShaderWeaver::CreateShaderParams(const sw::Evaluator& vert, const sw::Evaluator& frag) const
{
	pt0::Shader::Params sp(m_texture_names, m_layout);
	sp.vs = vert.GenShaderStr().c_str();
	sp.fs = frag.GenShaderStr().c_str();

	sp.uniform_names[pt0::U_MODEL_MAT] = MODEL_MAT_NAME;
	sp.uniform_names[pt0::U_VIEW_MAT]  = VIEW_MAT_NAME;
	sp.uniform_names[pt0::U_PROJ_MAT]  = PROJ_MAT_NAME;

	if (vert.HasNodeType<sw::node::Time>() || frag.HasNodeType<sw::node::Time>()) {
        sp.uniform_names[pt0::U_TIME]       = sw::node::Time::TimeName();
        sp.uniform_names[pt0::U_SINE_TIME]  = sw::node::Time::SineTimeName();
        sp.uniform_names[pt0::U_COS_TIME]   = sw::node::Time::CosTimeName();
        sp.uniform_names[pt0::U_DELTA_TIME] = sw::node::Time::DeltaTimeName();
	}

    if (vert.HasNodeType<sw::node::Raymarching>() || frag.HasNodeType<sw::node::Raymarching>()) {
        sp.uniform_names[pt0::U_RESOLUTION] = sw::node::Raymarching::ResolutionName();
    }

    if (vert.HasNodeType<sw::node::CameraPos>() || frag.HasNodeType<sw::node::CameraPos>()) {
        sp.uniform_names[pt0::U_CAM_POS] = sw::node::CameraPos::CamPosName();
    }

	return sp;
}

}