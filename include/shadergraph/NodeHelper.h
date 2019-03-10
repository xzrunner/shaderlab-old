#pragma once

#include <blueprint/typedef.h>

#include <node0/typedef.h>

namespace bp { class Pins; }

namespace sg
{

class NodeHelper
{
public:
	static void RemoveDefaultNode(const bp::Pins& p);

    static void LoadFunctionNode(const n0::SceneNodePtr& obj, const bp::NodePtr& node);

}; // NodeHelper

}