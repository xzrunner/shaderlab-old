#include "shadergraph/NodeBuilder.h"
#include "shadergraph/Pins.h"

#include "shadergraph/node/Sprite.h"
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Vector1.h"
#include "shadergraph/node/Vector2.h"
#include "shadergraph/node/Vector3.h"
#include "shadergraph/node/Vector4.h"
#include "shadergraph/node/UV.h"
#include "shadergraph/node/Add.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Divide.h"
#include "shadergraph/node/Lerp.h"
#include "shadergraph/node/InverseLerp.h"
#include "shadergraph/node/Remap.h"
#include "shadergraph/node/SampleTex2D.h"
#include "shadergraph/node/Tex2DAsset.h"
// input
#include "shadergraph/node/Time.h"

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
	if (type == node::Sprite::GetClassName())
	{
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_MUL,
			node::Vector3::GetClassName(), "mul"))->SetValue(sm::vec3(1, 1, 1));
		std::static_pointer_cast<node::Vector3>(CreateDefault(nodes, node, node::Sprite::ID_COL_ADD,
			node::Vector3::GetClassName(), "add"))->SetValue(sm::vec3(0, 0, 0));
	}
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
	else if (type == node::SampleTex2D::GetClassName())
	{
		std::static_pointer_cast<node::Tex2DAsset>(CreateDefault(nodes, node, node::SampleTex2D::ID_TEX,
			node::Tex2DAsset::GetClassName()));
		std::static_pointer_cast<node::Tex2DAsset>(CreateDefault(nodes, node, node::SampleTex2D::ID_UV,
			node::UV::GetClassName()));
	}
	else if (type == node::Add::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Subtract::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Multiply::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Divide::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 0, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, 1, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Lerp::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_A, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_B, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Lerp::ID_T, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::InverseLerp::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_A, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_B, node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::InverseLerp::ID_T, node::Vector1::GetClassName()))->SetValue(0);
	}
	else if (type == node::Remap::GetClassName())
	{
		std::static_pointer_cast<node::Vector1>(CreateDefault(nodes, node, node::Remap::ID_IN,   node::Vector1::GetClassName()))->SetValue(0);
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Remap::ID_FROM, node::Vector2::GetClassName()))->SetValue(sm::vec2(-1, 1));
		std::static_pointer_cast<node::Vector2>(CreateDefault(nodes, node, node::Remap::ID_TO,   node::Vector2::GetClassName()))->SetValue(sm::vec2(0, 1));
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