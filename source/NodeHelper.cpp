#include "shadergraph/NodeHelper.h"

#include <blueprint/Connecting.h>
#include <blueprint/Pins.h>
#include <blueprint/Node.h>

namespace sg
{

void NodeHelper::RemoveDefaultNode(const bp::Pins& p)
{
	auto& conns = p.GetConnecting();
	if (conns.empty()) {
		return;
	}
	auto& pair = conns[0]->GetFrom();
	assert(pair);
    if (pair->GetConnecting().size() == 1)
    {
        auto& parent = pair->GetParent();
        // fixme: is default input param
        if (parent.IsStyleOnlyTitle()) {
            parent.SetLifeDeleteLater(true);
        }
    }
}

}