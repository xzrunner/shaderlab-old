#include "shadergraph/ShaderGraph.h"
#include "shadergraph/NodeBuilder.h"
#include "shadergraph/NodeHelper.h"
#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

#include <blueprint/NodeBuilder.h>
#include <blueprint/Pins.h>

namespace sg
{

CU_SINGLETON_DEFINITION(ShaderGraph);

extern void regist_rttr();

ShaderGraph::ShaderGraph()
{
	regist_rttr();

	Init();
	InitNodes();
}

void ShaderGraph::Init()
{
	bp::NodeBuilder::Callback cb;
	cb.after_created = [](bp::Node& node, std::vector<n0::SceneNodePtr>& nodes) {
		NodeBuilder::CreateDefaultInputs(nodes, node);
	};
	cb.before_connected = [](bp::Pins& from, bp::Pins& to) {
		NodeHelper::RemoveDefaultNode(to);
	};
	cb.after_connected = [](bp::Pins& from, bp::Pins& to) {
		NodeHelper::TypePromote(from, to);
		NodeHelper::TypePromote(from.GetParent());
		NodeHelper::TypePromote(to.GetParent());
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