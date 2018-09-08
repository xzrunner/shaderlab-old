#include "shadergraph/ShaderGraph.h"

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
#include "shadergraph/node/PhongModel.h"

#include <blueprint/NodeFactory.h>

namespace shadergraph
{

void ShaderGraph::Init()
{
	std::vector<std::shared_ptr<bp::Node>> nodes;

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
	nodes.push_back(std::make_shared<node::PhongModel>());

	bp::NodeFactory::Instance()->RegistNodes(nodes);
}

}