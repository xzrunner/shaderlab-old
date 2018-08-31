#include "ematerial/NodeFactory.h"

#include "ematerial/Constant1.h"
#include "ematerial/Constant2.h"
#include "ematerial/Constant3.h"
#include "ematerial/Constant4.h"
#include "ematerial/Add.h"
#include "ematerial/Subtract.h"
#include "ematerial/Multiply.h"
#include "ematerial/Divide.h"
#include "ematerial/PhongModel.h"
#include "ematerial/TextureObject.h"

namespace ematerial
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

	m_nodes.push_back(std::make_shared<PhongModel>());
}

}