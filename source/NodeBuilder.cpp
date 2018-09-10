#include "shadergraph/NodeBuilder.h"
#include "shadergraph/node/Sprite.h"
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Phong2.h"
#include "shadergraph/node/Constant1.h"
#include "shadergraph/node/Constant3.h"

#include <painting3/Material.h>
#include <node0/SceneNode.h>
#include <node0/CompIdentity.h>
#include <node2/CompTransform.h>
#include <node2/CompBoundingBox.h>
#include <blueprint/CompNode.h>
#include <blueprint/Connecting.h>
#include <blueprint/NodeFactory.h>

namespace sg
{

std::shared_ptr<bp::Node> NodeBuilder::Create(const std::string& type,
	                                          std::vector<n0::SceneNodePtr>& nodes,
	                                          const sm::vec2& pos)
{
	auto bp_node = bp::NodeFactory::Instance()->Create(type);
	if (!bp_node) {
		return nullptr;
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

	if (type == node::Sprite::TYPE_NAME)
	{

		float x = -150, y = -50;
		const float dx = 0, dy = -50;

		auto mul = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(mul)->SetValue(sm::vec3(1, 1, 1));
		bp::make_connecting(
			mul->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Sprite::ID_COL_MUL]
		);
		x += dx, y += dy;

		auto add = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(add)->SetValue(sm::vec3(0, 0, 0));
		bp::make_connecting(
			add->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Sprite::ID_COL_ADD]
		);
		x += dx, y += dy;
	}
	else if (type == node::Phong::TYPE_NAME)
	{
		pt3::Material mat;

		float x = -150, y = 100;
		const float dx = 0, dy = -50;

		auto ambient = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(ambient)->SetValue(mat.ambient);
		bp::make_connecting(
			ambient->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong::ID_AMBIENT]
		);
		x += dx, y += dy;

		auto diffuse = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(diffuse)->SetValue(mat.diffuse);
		bp::make_connecting(
			diffuse->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong::ID_DIFFUSE]
		);
		x += dx, y += dy;

		auto specular = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(specular)->SetValue(mat.specular);
		bp::make_connecting(
			specular->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong::ID_SPECULAR]
		);
		x += dx, y += dy;

		auto shininess = Create(node::Constant1::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant1>(shininess)->SetValue(mat.shininess);
		bp::make_connecting(
			shininess->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong::ID_SHININESS]
		);
		x += dx, y += dy;
	}
	else if (type == node::Phong2::TYPE_NAME)
	{
		sm::vec3 light_pos(1.2f, 1.0f, 2.0f);
		sm::vec3 light_ambient(0.2f, 0.2f, 0.2f);
		sm::vec3 light_diffuse(0.5f, 0.5f, 0.5f);
		sm::vec3 light_specular(1.0f, 1.0f, 1.0f);

		sm::vec3 material_diffuse(1, 0, 0);
		sm::vec3 material_specular(0, 0.5f, 0);
		float material_shininess(64.0f);
		sm::vec3 material_emission(0, 0, 0);

		sm::vec3 view_pos(1.2f, 1.0f, 2.0f);

		float x = -150, y = 200;
		const float dx = 0, dy = -50;

		// light

		auto lit_pos = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(lit_pos)->SetValue(light_pos);
		bp::make_connecting(
			lit_pos->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_LIT_POSITION]
		);
		x += dx, y += dy;

		auto lit_ambient = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(lit_ambient)->SetValue(light_ambient);
		bp::make_connecting(
			lit_ambient->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_LIT_AMBIENT]
		);
		x += dx, y += dy;

		auto lit_diffuse = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(lit_diffuse)->SetValue(light_diffuse);
		bp::make_connecting(
			lit_diffuse->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_LIT_DIFFUSE]
		);
		x += dx, y += dy;

		auto lit_specular = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(lit_specular)->SetValue(light_specular);
		bp::make_connecting(
			lit_specular->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_LIT_SPECULAR]
		);
		x += dx, y += dy;

		// material

		auto mat_diffuse = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(mat_diffuse)->SetValue(material_diffuse);
		bp::make_connecting(
			mat_diffuse->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_MAT_DIFFUSE]
		);
		x += dx, y += dy;

		auto mat_specular = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(mat_specular)->SetValue(material_specular);
		bp::make_connecting(
			mat_specular->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_MAT_SPECULAR]
		);
		x += dx, y += dy;

		auto mat_shininess = Create(node::Constant1::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant1>(mat_shininess)->SetValue(material_shininess);
		bp::make_connecting(
			mat_shininess->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_MAT_SHININESS]
		);
		x += dx, y += dy;

		auto mat_emission = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(mat_emission)->SetValue(material_emission);
		bp::make_connecting(
			mat_emission->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_MAT_EMISSION]
		);
		x += dx, y += dy;

		// view

		auto vp = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(vp)->SetValue(view_pos);
		bp::make_connecting(
			vp->GetAllOutput()[0],
			bp_node->GetAllInput()[node::Phong2::ID_VIEW_POS]
		);
		x += dx, y += dy;
	}

	nodes.push_back(node);

	return bp_node;
}

}