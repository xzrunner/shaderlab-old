#include "shadergraph/ShaderGraph.h"
#include "shadergraph/NodeBuilder.h"
#include "shadergraph/Node.h"
#include "shadergraph/PinCallback.h"
#include "shadergraph/TypeDeduction.h"

#include <blueprint/NodeBuilder.h>
#include <blueprint/Pin.h>
#include <blueprint/NodeHelper.h>

#include <shaderweaver/ShaderWeaver.h>

namespace sg
{

CU_SINGLETON_DEFINITION(ShaderGraph);

extern void regist_rttr();

ShaderGraph::ShaderGraph()
{
	sw::ShaderWeaver::Instance();

	regist_rttr();

	Init();
	InitNodes();

    InitPinCallback();
}

void ShaderGraph::Init()
{
	bp::NodeBuilder::Callback cb;
	cb.on_created = [](bp::Node& node, std::vector<n0::SceneNodePtr>& nodes) {
		NodeBuilder::CreateDefaultInputs(nodes, node);
	};
	cb.on_connecting = [](bp::Pin& from, bp::Pin& to) {
		bp::NodeHelper::RemoveDefaultNode(to);
	};
	cb.on_connected = [](bp::Pin& from, bp::Pin& to) {
        TypeDeduction::DeduceConn(from, to);
	};
    cb.on_disconnected = [](bp::Pin& from, bp::Pin& to) {
        TypeDeduction::DeduceNode(from.GetParent());
        TypeDeduction::DeduceNode(to.GetParent());
    };
	bp::NodeBuilder::Instance()->RegistCB(cb);
}

void ShaderGraph::InitNodes()
{
	auto list = rttr::type::get<Node>().get_derived_classes();
	m_nodes.reserve(list.size());
	for (auto& t : list)
	{
		auto obj = t.create();
		assert(obj.is_valid());
		auto node = obj.get_value<bp::NodePtr>();
		assert(node);
		m_nodes.push_back(node);
	}
}

}