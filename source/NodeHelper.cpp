#include "shadergraph/NodeHelper.h"

#include <blueprint/Connecting.h>
#include <blueprint/Pins.h>
#include <blueprint/Node.h>
#include <blueprint/node/Function.h>

#include <ns/CompFactory.h>
#include <node0/SceneNode.h>
#include <node0/CompComplex.h>
#include <node2/CompBoundingBox.h>

namespace sg
{

void NodeHelper::RemoveDefaultNode(const bp::Pins& p)
{
	auto& conns = p.GetConnecting();
	if (conns.empty()) {
		return;
	}
	auto& pair = conns[0]->GetFrom();
	assert(pair);
    if (pair->GetConnecting().size() == 1)
    {
        auto& parent = pair->GetParent();
        // fixme: is default input param
        if (parent.IsStyleOnlyTitle()) {
            parent.SetLifeDeleteLater(true);
        }
    }
}

void NodeHelper::LoadFunctionNode(const n0::SceneNodePtr& obj, const bp::NodePtr& node)
{
    assert(node->get_type() == rttr::type::get<bp::node::Function>());

    auto func_node = std::static_pointer_cast<bp::node::Function>(node);
    n0::CompAssetPtr casset = ns::CompFactory::Instance()->CreateAsset(func_node->GetFilepath());
    assert(casset->TypeID() == n0::GetAssetUniqueTypeID<n0::CompComplex>());
    auto& ccomplex = std::static_pointer_cast<n0::CompComplex>(casset);
    bp::node::Function::SetChildren(func_node, ccomplex->GetAllChildren());

    // update aabb
    auto& st = node->GetStyle();
    obj->GetUniqueComp<n2::CompBoundingBox>().SetSize(
        *obj, sm::rect(st.width, st.height)
    );
}

}