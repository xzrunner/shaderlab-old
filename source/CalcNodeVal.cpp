#include "ematerial/CalcNodeVal.h"
#include "ematerial/Constant1.h"
#include "ematerial/Constant2.h"
#include "ematerial/Constant3.h"
#include "ematerial/Constant4.h"

#include <blueprint/Pins.h>
#include <blueprint/Connecting.h>

namespace ematerial
{

sm::vec3 CalcNodeVal::ToVec3(const bp::node::Pins& pin)
{
	sm::vec3 ret;

	auto& conn = pin.GetConnecting();
	assert(conn.size() <= 1);
	if (conn.empty() || !conn[0]) {
		return ret;
	}

	auto& from = conn[0]->GetFrom();
	if (!from) {
		return ret;
	}

	auto& node = from->GetParent();
	if (node.TypeID() == bp::GetNodeTypeID<Constant1>())
	{
		auto& c1 = dynamic_cast<const Constant1&>(node);
		auto& v = c1.GetValue();
		ret.Set(v, v, v);
	}
	else if (node.TypeID() == bp::GetNodeTypeID<Constant2>())
	{
		auto& c2 = dynamic_cast<const Constant2&>(node);
		auto& v = c2.GetValue();
		ret.Set(v.x, v.y, 0);
	}
	else if (node.TypeID() == bp::GetNodeTypeID<Constant3>())
	{
		auto& c3 = dynamic_cast<const Constant3&>(node);
		ret = c3.GetValue();
	}
	else if (node.TypeID() == bp::GetNodeTypeID<Constant4>())
	{
		auto& c4 = dynamic_cast<const Constant4&>(node);
		auto& v = c4.GetValue();
		ret.Set(v.x, v.y, v.z);
	}

	return ret;
}

float CalcNodeVal::ToFloat(const bp::node::Pins& pin)
{
	float ret = 0;

	auto& conn = pin.GetConnecting();
	assert(conn.size() <= 1);
	if (conn.empty() || !conn[0]) {
		return ret;
	}

	auto& from = conn[0]->GetFrom();
	if (!from) {
		return ret;
	}

	auto& node = from->GetParent();
	if (node.TypeID() == bp::GetNodeTypeID<Constant1>())
	{
		auto& c1 = dynamic_cast<const Constant1&>(node);
		ret = c1.GetValue();
	}

	return ret;
}

}