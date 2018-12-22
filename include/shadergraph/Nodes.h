#pragma once

#include "shadergraph/Node.h"

namespace sg
{

void nodes_regist_rttr();

namespace node
{

#define SG_NODE(name, preview, debug)                    \
class name : public Node                                 \
{                                                        \
public:                                                  \
	name()                                               \
		: Node(#name, preview, debug)                    \
	{                                                    \
		InitPins(#name);                                 \
	}                                                    \
                                                         \
	RTTR_ENABLE(Node)                                    \
};

SG_NODE(Sphere, false, false)
SG_NODE(Torus, false, false)

}
}