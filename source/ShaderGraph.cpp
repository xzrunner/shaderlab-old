#include "shadergraph/ShaderGraph.h"
#include "shadergraph/NodeBuilder.h"
#include "shadergraph/NodeHelper.h"

// register nodes to factory
#include "shadergraph/node/Constant1.h"
#include "shadergraph/node/Constant2.h"
#include "shadergraph/node/Constant3.h"
#include "shadergraph/node/Constant4.h"
#include "shadergraph/node/Add.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Divide.h"
#include "shadergraph/node/TextureObject.h"
#include "shadergraph/node/TextureSample.h"
#include "shadergraph/node/Sprite.h"
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Phong2.h"

#include <blueprint/NodeFactory.h>
#include <blueprint/NodeBuilder.h>
#include <blueprint/Pins.h>

namespace sg
{

void ShaderGraph::Init()
{
	std::vector<bp::NodePtr> nodes;

	nodes.push_back(std::make_shared<node::Constant1>());
	nodes.push_back(std::make_shared<node::Constant2>());
	nodes.push_back(std::make_shared<node::Constant3>());
	nodes.push_back(std::make_shared<node::Constant4>());

	nodes.push_back(std::make_shared<node::Add>());
	nodes.push_back(std::make_shared<node::Subtract>());
	nodes.push_back(std::make_shared<node::Multiply>());
	nodes.push_back(std::make_shared<node::Divide>());

	nodes.push_back(std::make_shared<node::TextureObject>());
	nodes.push_back(std::make_shared<node::TextureSample>());

	nodes.push_back(std::make_shared<node::Sprite>());
	nodes.push_back(std::make_shared<node::Phong>());
	nodes.push_back(std::make_shared<node::Phong2>());

	bp::NodeFactory::Instance()->RegistNodes(nodes);

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