#pragma once

#include <SM_Vector.h>

namespace bp { class Pins; }

namespace shadergraph
{

class Utility
{
public:
	static sm::vec3 CalcNodeInputVal(const bp::Pins& pin);

}; // Utility

}