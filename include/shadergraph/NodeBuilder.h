#pragma once

#include <node0/typedef.h>
#include <SM_Vector.h>

#include <string>
#include <vector>

namespace bp { namespace node { class Node; } }

namespace shadergraph
{

class NodeBuilder
{
public:
	static std::shared_ptr<bp::node::Node>
		Create(const std::string& type,
			   std::vector<n0::SceneNodePtr>& nodes,
			   const sm::vec2& pos = sm::vec2(0, 0));

}; // NodeBuilder

}