#include "ematerial/Utility.h"
#include "ematerial/Node.h"

#include <blueprint/Connecting.h>

namespace ematerial
{

sm::vec3 Utility::CalcNodeInputVal(const bp::node::Pins& pin)
{
	sm::vec3 ret;
	auto& conn = pin.GetConnecting();
	if (conn.empty()) {
		return ret;
	}
	assert(conn.size() == 1);
	auto from = conn[0]->GetFrom();
	if (!from) {
		return ret;
	}
	return static_cast<const Node&>(from->GetParent()).ToVec3();
}

}