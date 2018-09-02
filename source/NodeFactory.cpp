#include "shadergraph/NodeFactory.h"

#include "shadergraph/Constant1.h"
#include "shadergraph/Constant2.h"
#include "shadergraph/Constant3.h"
#include "shadergraph/Constant4.h"
#include "shadergraph/Add.h"
#include "shadergraph/Subtract.h"
#include "shadergraph/Multiply.h"
#include "shadergraph/Divide.h"
#include "shadergraph/PhongModel.h"
#include "shadergraph/TextureObject.h"
#include "shadergraph/TextureSample.h"

namespace shadergraph
{

CU_SINGLETON_DEFINITION(NodeFactory);

NodeFactory::NodeFactory()
{
	RegistAllNode();
}

std::shared_ptr<bp::node::Node> NodeFactory::Create(const std::string& type)
{
	for (auto& n : m_nodes) {
		if (n->TypeName() == type) {
			return n->Create();
		}
	}
	return nullptr;
}

void NodeFactory::RegistAllNode()
{
	m_nodes.push_back(std::make_shared<Constant1>());
	m_nodes.push_back(std::make_shared<Constant2>());
	m_nodes.push_back(std::make_shared<Constant3>());
	m_nodes.push_back(std::make_shared<Constant4>());

	m_nodes.push_back(std::make_shared<Add>());
	m_nodes.push_back(std::make_shared<Subtract>());
	m_nodes.push_back(std::make_shared<Multiply>());
	m_nodes.push_back(std::make_shared<Divide>());

	m_nodes.push_back(std::make_shared<TextureObject>());
	m_nodes.push_back(std::make_shared<TextureSample>());

	m_nodes.push_back(std::make_shared<PhongModel>());
}

}