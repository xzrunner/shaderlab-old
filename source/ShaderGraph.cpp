#include "shadergraph/ShaderGraph.h"

// register nodes to factory
#include "shadergraph/Constant1.h"
#include "shadergraph/Constant2.h"
#include "shadergraph/Constant3.h"
#include "shadergraph/Constant4.h"
#include "shadergraph/Add.h"
#include "shadergraph/Subtract.h"
#include "shadergraph/Multiply.h"
#include "shadergraph/Divide.h"
#include "shadergraph/Sprite.h"
#include "shadergraph/PhongModel.h"
#include "shadergraph/TextureObject.h"
#include "shadergraph/TextureSample.h"

#include <blueprint/NodeFactory.h>

namespace shadergraph
{

void ShaderGraph::Init()
{
	std::vector<std::shared_ptr<bp::Node>> nodes;

	nodes.push_back(std::make_shared<Constant1>());
	nodes.push_back(std::make_shared<Constant2>());
	nodes.push_back(std::make_shared<Constant3>());
	nodes.push_back(std::make_shared<Constant4>());

	nodes.push_back(std::make_shared<Add>());
	nodes.push_back(std::make_shared<Subtract>());
	nodes.push_back(std::make_shared<Multiply>());
	nodes.push_back(std::make_shared<Divide>());

	nodes.push_back(std::make_shared<TextureObject>());
	nodes.push_back(std::make_shared<TextureSample>());

	nodes.push_back(std::make_shared<Sprite>());
	nodes.push_back(std::make_shared<PhongModel>());

	bp::NodeFactory::Instance()->RegistNodes(nodes);
}

}