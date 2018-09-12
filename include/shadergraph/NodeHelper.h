#pragma once

namespace bp { class Node; class Pins; }

namespace sg
{

class NodeHelper
{
public:
	static void TypePromote(const bp::Pins& p0, const bp::Pins& p1);
	static void TypePromote(const bp::Node& node);

	static void RemoveDefaultNode(const bp::Pins& p);

private:
	static void SetPinsType(bp::Pins& pins, int type);

}; // NodeHelper

}