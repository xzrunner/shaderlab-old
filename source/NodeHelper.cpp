#include "shadergraph/NodeHelper.h"
#include "shadergraph/Pins.h"

#include "shadergraph/node/Add.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Divide.h"

#include <blueprint/Pins.h>
#include <blueprint/Node.h>
#include <blueprint/Connecting.h>

#include <algorithm>

namespace sg
{


void NodeHelper::TypePromote(const bp::Pins& p0, const bp::Pins& p1)
{
	int type0 = p0.GetType();
	int type1 = p1.GetType();
	if (type0 == type1) {
		return;
	}

	if (type0 >= PINS_VECTOR1 && type0 <= PINS_VECTOR4 &&
		type1 >= PINS_VECTOR1 && type1 <= PINS_VECTOR4)
	{
		int type = std::max(type0, type1);
		SetPinsType(const_cast<bp::Pins&>(p0), type);
		SetPinsType(const_cast<bp::Pins&>(p1), type);
	}
}

void NodeHelper::TypePromote(const bp::Node& node)
{
	auto type = node.TypeName();
	if (type == node::Add::TYPE_NAME ||
		type == node::Subtract::TYPE_NAME ||
		type == node::Multiply::TYPE_NAME ||
		type == node::Divide::TYPE_NAME)
	{
		PinsType type = PINS_VECTOR1;

		for (auto& p : node.GetAllInput()) {
			if (p->GetType() > type) {
				type = static_cast<PinsType>(p->GetType());
			}
		}
		for (auto& p : node.GetAllOutput()) {
			if (p->GetType() > type) {
				type = static_cast<PinsType>(p->GetType());
			}
		}
		assert(type <= PINS_VECTOR4);

		for (auto& p : node.GetAllInput()) {
			SetPinsType(*p, type);
		}
		for (auto& p : node.GetAllOutput()) {
			SetPinsType(*p, type);
		}
	}
}

void NodeHelper::RemoveDefaultNode(const bp::Pins& p)
{
	auto& conns = p.GetConnecting();
	if (conns.empty()) {
		return;
	}
	auto& pair = conns[0]->GetFrom();
	assert(pair);
	pair->GetParent().SetLifeDeleteLater(true);
}

void NodeHelper::SetPinsType(bp::Pins& pins, int type)
{
	if (pins.GetType() == type) {
		return;
	}

	pins.SetType(type);
	for (auto& conn : pins.GetConnecting()) {
		conn->UpdateCurve();
	}
}

}