#include "shadergraph/NodeBuilder.h"
#include "shadergraph/Pins.h"

#include "shadergraph/node/Sprite.h"
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Constant1.h"
#include "shadergraph/node/Constant2.h"
#include "shadergraph/node/Constant3.h"
#include "shadergraph/node/Constant4.h"
#include "shadergraph/node/Input.h"
#include "shadergraph/node/Add.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Divide.h"
#include "shadergraph/node/TextureSample.h"
#include "shadergraph/node/TextureObject.h"

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
	auto type = node.TypeName();
	if (type == node::Sprite::TYPE_NAME)
	{
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Sprite::ID_COL_MUL,
			node::Constant3::TYPE_NAME, "mul"))->SetValue(sm::vec3(1, 1, 1));
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Sprite::ID_COL_ADD,
			node::Constant3::TYPE_NAME, "add"))->SetValue(sm::vec3(0, 0, 0));
	}
	else if (type == node::Phong::TYPE_NAME)
	{
		// light
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_LIT_POSITION,
			node::Constant3::TYPE_NAME, "lit_pos"))->SetValue(sm::vec3(1.2f, 1.0f, 2.0f));
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_LIT_AMBIENT,
			node::Constant3::TYPE_NAME, "lit_ambient"))->SetValue(sm::vec3(0.2f, 0.2f, 0.2f));
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_LIT_DIFFUSE,
			node::Constant3::TYPE_NAME, "lit_diffuse"))->SetValue(sm::vec3(0.5f, 0.5f, 0.5f));
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_LIT_SPECULAR,
			node::Constant3::TYPE_NAME, "lit_specular"))->SetValue(sm::vec3(1.0f, 1.0f, 1.0f));
		// material
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_MAT_DIFFUSE,
			node::Constant3::TYPE_NAME, "mat_diffuse"))->SetValue(sm::vec3(1, 0, 0));
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_MAT_SPECULAR,
			node::Constant3::TYPE_NAME, "mat_specular"))->SetValue(sm::vec3(0, 0.5f, 0));
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, node::Phong::ID_MAT_SHININESS,
			node::Constant1::TYPE_NAME, "mat_shininess"))->SetValue(64.0f);
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_MAT_EMISSION,
			node::Constant3::TYPE_NAME, "mat_emission"))->SetValue(sm::vec3(0, 0, 0));
		// view
		std::static_pointer_cast<node::Constant3>(CreateDefault(nodes, node, node::Phong::ID_VIEW_POS,
			node::Constant3::TYPE_NAME, "view_pos"))->SetValue(sm::vec3(1.2f, 1.0f, 2.0f));
	}
	else if (type == node::Add::TYPE_NAME)
	{
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 0, node::Constant1::TYPE_NAME))->SetValue(0);
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 1, node::Constant1::TYPE_NAME))->SetValue(0);
	}
	else if (type == node::Subtract::TYPE_NAME)
	{
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 0, node::Constant1::TYPE_NAME))->SetValue(0);
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 1, node::Constant1::TYPE_NAME))->SetValue(0);
	}
	else if (type == node::Multiply::TYPE_NAME)
	{
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 0, node::Constant1::TYPE_NAME))->SetValue(0);
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 1, node::Constant1::TYPE_NAME))->SetValue(0);
	}
	else if (type == node::Divide::TYPE_NAME)
	{
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 0, node::Constant1::TYPE_NAME))->SetValue(0);
		std::static_pointer_cast<node::Constant1>(CreateDefault(nodes, node, 1, node::Constant1::TYPE_NAME))->SetValue(0);
	}
	else if (type == node::TextureSample::TYPE_NAME)
	{
		std::static_pointer_cast<node::TextureObject>(CreateDefault(nodes, node, node::TextureSample::ID_TEX,
			node::TextureObject::TYPE_NAME));
		std::static_pointer_cast<node::Input>(CreateDefault(nodes, node, node::TextureSample::ID_UV,
			node::Input::TYPE_NAME))->SetName("v_texcoord").SetType(sg::PINS_VECTOR2);
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