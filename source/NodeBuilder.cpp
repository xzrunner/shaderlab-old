#include "shadergraph/NodeBuilder.h"
#include "shadergraph/RegistNodes.h"
#include "shadergraph/Pins.h"
#include "shadergraph/Utility.h"

#include <node0/SceneNode.h>
#include <node0/CompIdentity.h>
#include <node2/CompTransform.h>
#include <node2/CompBoundingBox.h>
#include <blueprint/CompNode.h>
#include <blueprint/Connecting.h>
#include <blueprint/NodeLayout.h>
#include <shaderweaver/Node.h>
#include <shaderweaver/node/Raymarching.h>

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

	bp_node->SetPos(pos);

    if (is_default && bp_node->GetAllInput().size() <= 1 && bp_node->GetAllOutput().size() <= 1) {
        bp_node->SetStyleOnlyTitle(true);
        bp::NodeLayout::UpdateNodeStyle(*bp_node);
    }

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

	// default from rttr

	auto cls_name = type.get_name().to_string();
	cls_name = "sw::" + cls_name.substr(cls_name.find("sg::") + strlen("sg::"));
	rttr::type t = rttr::type::get_by_name(cls_name);
	if (!t.is_valid()) {
		return;
	}
	auto ctor = t.get_constructor();
	if (!ctor.is_valid()) {
		return;
	}

	rttr::variant var = ctor.invoke();
	assert(var.is_valid());

	auto method_imports = t.get_method("GetImports");
	assert(method_imports.is_valid());
	auto var_imports = method_imports.invoke(var);
	assert(var_imports.is_valid()
		&& var_imports.is_type<std::vector<sw::Node::Port>>());
	auto& imports = var_imports.get_value<std::vector<sw::Node::Port>>();

	for (int i = 0, n = node.GetAllInput().size(); i < n; ++i)
	{
		auto& pins = node.GetAllInput()[i];

        std::string default_type_str;

        auto default_val = ctor.get_metadata(i);

        int pins_type = pins->GetType();
        if (pins_type == PINS_DYNAMIC_VECTOR)
        {
            if (default_val.is_type<float>()) {
                pins_type = PINS_VECTOR1;
            } else if (default_val.is_type<sm::vec2>()) {
                pins_type = PINS_VECTOR2;
            } else if (default_val.is_type<sm::vec3>()) {
                pins_type = PINS_VECTOR3;
            } else if (default_val.is_type<sm::vec4>()) {
                pins_type = PINS_VECTOR4;
            } else {
                assert(0);
            }
        }
        else if (pins_type == PINS_DYNAMIC_MATRIX)
        {
            if (default_val.is_type<sm::mat2>()) {
                pins_type = PINS_MATRIX2;
            } else if (default_val.is_type<sm::mat3>()) {
                pins_type = PINS_MATRIX3;
            } else if (default_val.is_type<sm::mat4>()) {
                pins_type = PINS_MATRIX4;
            } else {
                assert(0);
            }
        }

		switch (pins_type)
		{
		case PINS_BOOLEAN:
			default_type_str = rttr::type::get<node::Boolean>().get_name().to_string();
			break;
		case PINS_VECTOR1:
			default_type_str = rttr::type::get<node::Vector1>().get_name().to_string();
			break;
		case PINS_VECTOR2:
			if (imports[i].var.GetType().interp == sw::VT_TEX) {
				default_type_str = rttr::type::get<node::UV>().get_name().to_string();
			} else {
				default_type_str = rttr::type::get<node::Vector2>().get_name().to_string();
			}
			break;
		case PINS_VECTOR3: case PINS_COLOR:
			default_type_str = rttr::type::get<node::Vector3>().get_name().to_string();
			break;
		case PINS_VECTOR4:
			default_type_str = rttr::type::get<node::Vector4>().get_name().to_string();
			break;
		case PINS_TEXTURE2D:
			default_type_str = rttr::type::get<node::Tex2DAsset>().get_name().to_string();
			break;
		case PINS_MATRIX2:
			default_type_str = rttr::type::get<node::Matrix2>().get_name().to_string();
			break;
		case PINS_MATRIX3:
			default_type_str = rttr::type::get<node::Matrix3>().get_name().to_string();
			break;
		case PINS_MATRIX4:
			default_type_str = rttr::type::get<node::Matrix4>().get_name().to_string();
			break;
		case PINS_FUNCTION:
        {
            auto method = t.get_method("QueryNesting");
            assert(method.is_valid());
            auto nest = method.invoke(var, imports[i].var.GetName());
            assert(nest.is_valid() && nest.is_type<std::string>());
            default_type_str = nest.get_value<std::string>();
            default_type_str = "sg::" + default_type_str.substr(default_type_str.find("sw::") + strlen("sw::"));
        }
			break;
		default:
			assert(0);
		}

		if (default_type_str.empty()) {
			continue;
		}

		auto default_node = CreateDefault(nodes, node, i, default_type_str);
		switch (pins_type)
		{
		case PINS_BOOLEAN:
			if (default_val.is_valid()) {
				assert(default_val.is_type<bool>());
				std::static_pointer_cast<node::Boolean>(default_node)->SetValue(
					default_val.to_bool()
				);
			} else {
				std::static_pointer_cast<node::Boolean>(default_node)->SetValue(false);
			}
			break;
		case PINS_VECTOR1:
			if (default_val.is_valid()) {
				assert(default_val.is_type<float>());
				std::static_pointer_cast<node::Vector1>(default_node)->SetValue(
					default_val.to_float()
				);
			} else {
				std::static_pointer_cast<node::Vector1>(default_node)->SetValue(0);
			}
			break;
		case PINS_VECTOR2:
			if (default_val.is_valid()) {
				assert(default_val.is_type<sm::vec2>());
				std::static_pointer_cast<node::Vector2>(default_node)->SetValue(
					default_val.get_value<sm::vec2>()
				);
			} else {
				std::static_pointer_cast<node::Vector2>(default_node)->SetValue(sm::vec2(0, 0));
			}
			break;
		case PINS_VECTOR3: case PINS_COLOR:
			if (default_val.is_valid()) {
				assert(default_val.is_type<sm::vec3>());
				std::static_pointer_cast<node::Vector3>(default_node)->SetValue(
					default_val.get_value<sm::vec3>()
				);
			} else {
				std::static_pointer_cast<node::Vector3>(default_node)->SetValue(sm::vec3(0, 0, 0));
			}
			break;
		case PINS_VECTOR4:
			if (default_val.is_valid()) {
				assert(default_val.is_type<sm::vec4>());
				std::static_pointer_cast<node::Vector4>(default_node)->SetValue(
					default_val.get_value<sm::vec4>()
				);
			} else {
				std::static_pointer_cast<node::Vector4>(default_node)->SetValue(sm::vec4(0, 0, 0, 0));
			}
			break;
        case PINS_TEXTURE2D:
        {
            auto var_name = Utility::CamelCaseToUnderscore(pins->GetName());
            std::static_pointer_cast<node::Tex2DAsset>(default_node)->SetName(var_name);
        }
            break;
		case PINS_MATRIX2:
			if (default_val.is_valid()) {
				assert(default_val.is_type<sm::mat2>());
				std::static_pointer_cast<node::Matrix2>(default_node)->SetValue(
					default_val.get_value<sm::mat2>()
				);
			} else {
				std::static_pointer_cast<node::Matrix2>(default_node)->SetValue(sm::mat2());
			}
			break;
		case PINS_MATRIX3:
			if (default_val.is_valid()) {
				assert(default_val.is_type<sm::mat3>());
				std::static_pointer_cast<node::Matrix3>(default_node)->SetValue(
					default_val.get_value<sm::mat3>()
				);
			} else {
				std::static_pointer_cast<node::Matrix3>(default_node)->SetValue(sm::mat3());
			}
			break;
		case PINS_MATRIX4:
			if (default_val.is_valid()) {
				assert(default_val.is_type<sm::mat4>());
				std::static_pointer_cast<node::Matrix4>(default_node)->SetValue(
					default_val.get_value<sm::mat4>()
				);
			} else {
				std::static_pointer_cast<node::Matrix4>(default_node)->SetValue(sm::mat4());
			}
			break;
		case PINS_FUNCTION:
			break;
		default:
			assert(0);
		}
	}

	// master
	if (type == rttr::type::get<node::Sprite>())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_MUL,
			rttr::type::get<node::Vector3>().get_name().to_string(), "mul"))->SetValue(sm::vec3(1, 1, 1));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_ADD,
			rttr::type::get<node::Vector3>().get_name().to_string(), "add"))->SetValue(sm::vec3(0, 0, 0));
	}
	else if (type == rttr::type::get<node::Raymarching>())
	{
		CreateDefault(nodes, node, sw::node::Raymarching::ID_SDF, rttr::type::get<node::Torus>().get_name().to_string());
//		CreateDefault(nodes, node, sw::node::Raymarching::ID_LIGHTING, rttr::type::get<node::PhongIllumination>().get_name().to_string());
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