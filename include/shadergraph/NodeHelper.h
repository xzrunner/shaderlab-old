#pragma once

#include <blueprint/typedef.h>

#include <node0/typedef.h>

#include <vector>

namespace bp { class Pins; }

namespace sg
{

class NodeHelper
{
public:
	static void RemoveDefaultNode(const bp::Pins& p);

    static void LoadFunctionNode(const n0::SceneNodePtr& obj, const bp::NodePtr& node);

    static void LoadConnections(const std::vector<n0::SceneNodePtr>& nodes,
        const std::string& filepath);

}; // NodeHelper

}