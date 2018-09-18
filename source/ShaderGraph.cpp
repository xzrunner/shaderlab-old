#include "shadergraph/ShaderGraph.h"
#include "shadergraph/NodeBuilder.h"
#include "shadergraph/NodeHelper.h"

#include <blueprint/NodeBuilder.h>
#include <blueprint/Pins.h>

namespace sg
{

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

}