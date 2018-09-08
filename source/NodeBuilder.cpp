#include "shadergraph/NodeBuilder.h"
#include "shadergraph/node/Sprite.h"
#include "shadergraph/node/PhongModel.h"
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

namespace shadergraph
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
	else if (type == node::PhongModel::TYPE_NAME)
	{
		pt3::Material mat;

		float x = -150, y = 100;
		const float dx = 0, dy = -50;

		auto ambient = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(ambient)->SetValue(mat.ambient);
		bp::make_connecting(
			ambient->GetAllOutput()[0],
			bp_node->GetAllInput()[node::PhongModel::ID_AMBIENT]
		);
		x += dx, y += dy;

		auto diffuse = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(diffuse)->SetValue(mat.diffuse);
		bp::make_connecting(
			diffuse->GetAllOutput()[0],
			bp_node->GetAllInput()[node::PhongModel::ID_DIFFUSE]
		);
		x += dx, y += dy;

		auto specular = Create(node::Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant3>(specular)->SetValue(mat.specular);
		bp::make_connecting(
			specular->GetAllOutput()[0],
			bp_node->GetAllInput()[node::PhongModel::ID_SPECULAR]
		);
		x += dx, y += dy;

		auto shininess = Create(node::Constant1::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<node::Constant1>(shininess)->SetValue(mat.shininess);
		bp::make_connecting(
			shininess->GetAllOutput()[0],
			bp_node->GetAllInput()[node::PhongModel::ID_SHININESS]
		);
		x += dx, y += dy;
	}

	nodes.push_back(node);

	return bp_node;
}

}