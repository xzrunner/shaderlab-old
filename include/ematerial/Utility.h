#pragma once

#include <SM_Vector.h>
#include <blueprint/Pins.h>

namespace ematerial
{

class Utility
{
public:
	static sm::vec3 CalcNodeInputVal(const bp::node::Pins& pin);

}; // Utility

}