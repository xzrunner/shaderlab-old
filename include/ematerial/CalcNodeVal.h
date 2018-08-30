#pragma once

#include <SM_Vector.h>
#include <blueprint/Node.h>

namespace ematerial
{

class CalcNodeVal
{
public:
	static sm::vec3 ToVec3(const bp::node::Pins& pin);
	static float ToFloat(const bp::node::Pins& pin);

}; // CalcNodeVal

}