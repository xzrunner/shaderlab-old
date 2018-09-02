#pragma once

#include <SM_Vector.h>

namespace bp { namespace node { class Pins; } }

namespace shadergraph
{

class Utility
{
public:
	static sm::vec3 CalcNodeInputVal(const bp::node::Pins& pin);

}; // Utility

}