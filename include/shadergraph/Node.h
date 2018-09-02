#pragma once

#include <blueprint/Node.h>

namespace shadergraph
{

class Node : public bp::node::Node
{
public:
	Node(const std::string& title)
		: bp::node::Node(title) {}

	virtual sm::vec3 ToVec3() const { return sm::vec3(); }

}; // Node

}