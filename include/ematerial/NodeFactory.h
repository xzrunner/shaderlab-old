#pragma once

#include <blueprint/Node.h>

#include <cu/cu_macro.h>

#include <memory>
#include <vector>

namespace ematerial
{

class NodeFactory
{
public:
	std::shared_ptr<bp::node::Node> Create(const std::string& type);

	auto& GetAllNodes() const { return m_nodes; }

private:
	void RegistAllNode();

private:
	std::vector<std::shared_ptr<bp::node::Node>> m_nodes;

	CU_SINGLETON_DECLARATION(NodeFactory)

}; // NodeFactory

}