#include "shadergraph/NodeBuilder.h"
#include "shadergraph/PhongModel.h"
#include "shadergraph/NodeFactory.h"
#include "shadergraph/Constant1.h"
#include "shadergraph/Constant3.h"

#include <painting3/Material.h>
#include <node0/SceneNode.h>
#include <node0/CompIdentity.h>
#include <node2/CompTransform.h>
#include <node2/CompBoundingBox.h>
#include <blueprint/CompNode.h>
#include <blueprint/Connecting.h>

namespace shadergraph
{

std::shared_ptr<bp::node::Node> NodeBuilder::Create(const std::string& type,
	                                                std::vector<n0::SceneNodePtr>& nodes,
	                                                const sm::vec2& pos)
{
	auto bp_node = NodeFactory::Instance()->Create(type);
	if (!bp_node) {
		return nullptr;
	}

	auto node = std::make_shared<n0::SceneNode>();
	auto& cnode = node->AddSharedComp<bp::CompNode>(bp_node);
	cnode.GetNode()->SetParent(node);
	auto& ctrans = node->AddUniqueComp<n2::CompTransform>();
	ctrans.SetPosition(*node, pos);
	node->AddUniqueComp<n0::CompIdentity>();
	auto& style = cnode.GetNode()->GetStyle();
	node->AddUniqueComp<n2::CompBoundingBox>(
		sm::rect(style.width, style.height)
	);

	if (type == PhongModel::TYPE_NAME)
	{
		pt3::Material mat;

		float x = -150, y = 100;
		const float dx = 0, dy = -50;

		auto ambient = Create(Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<Constant3>(ambient)->SetValue(mat.ambient);
		bp::node::make_connecting(
			ambient->GetAllOutput()[0],
			bp_node->GetAllInput()[PhongModel::ID_AMBIENT]
		);
		x += dx, y += dy;

		auto diffuse = Create(Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<Constant3>(diffuse)->SetValue(mat.diffuse);
		bp::node::make_connecting(
			diffuse->GetAllOutput()[0],
			bp_node->GetAllInput()[PhongModel::ID_DIFFUSE]
		);
		x += dx, y += dy;

		auto specular = Create(Constant3::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<Constant3>(specular)->SetValue(mat.specular);
		bp::node::make_connecting(
			specular->GetAllOutput()[0],
			bp_node->GetAllInput()[PhongModel::ID_SPECULAR]
		);
		x += dx, y += dy;

		auto shininess = Create(Constant1::TYPE_NAME, nodes, pos + sm::vec2(x, y));
		std::static_pointer_cast<Constant1>(shininess)->SetValue(mat.shininess);
		bp::node::make_connecting(
			shininess->GetAllOutput()[0],
			bp_node->GetAllInput()[PhongModel::ID_SHININESS]
		);
		x += dx, y += dy;
	}

	nodes.push_back(node);

	return bp_node;
}

}