#include "shadergraph/Utility.h"
#include "shadergraph/Node.h"

#include <blueprint/Connecting.h>
#include <blueprint/Pins.h>

namespace shadergraph
{

sm::vec3 Utility::CalcNodeInputVal(const bp::Pins& pin)
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