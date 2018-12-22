#include "shadergraph/Nodes.h"

namespace
{

#define REGIST_NODE_TYPE(name)                                \
	rttr::registration::class_<sg::node::name>("sg::"#name)   \
		.constructor<>()                                      \
	;

}

RTTR_REGISTRATION
{

REGIST_NODE_TYPE(Sphere)
REGIST_NODE_TYPE(Torus)

}

namespace sg
{
void nodes_regist_rttr()
{
}
}