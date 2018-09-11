#pragma once

namespace bp { class Pins; class Node; }

namespace sg
{

class NodeHelper
{
public:
	static void TypePromote(const bp::Pins& p0, const bp::Pins& p1);
	static void TypePromote(const bp::Node& node);

	static void RemoveDefaultNode(const bp::Pins& p);

}; // NodeHelper

}