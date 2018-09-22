#include "shadergraph/NodeHelper.h"
#include "shadergraph/Pins.h"
#include "shadergraph/Node.h"

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
	if (type0 >= PINS_DYNAMIC_VECTOR && type0 <= PINS_VECTOR4 &&
		type1 >= PINS_DYNAMIC_VECTOR && type1 <= PINS_VECTOR4 &&
		(p0.GetOldType() == PINS_DYNAMIC_VECTOR ||
		 p1.GetOldType() == PINS_DYNAMIC_VECTOR))
	{
		int type = std::max(type0, type1);
		SetPinsType(const_cast<bp::Pins&>(p0), type);
		SetPinsType(const_cast<bp::Pins&>(p1), type);
	}
	if (type0 >= PINS_DYNAMIC_MATRIX && type0 <= PINS_MATRIX4 &&
		type1 >= PINS_DYNAMIC_MATRIX && type1 <= PINS_MATRIX4 &&
		(p0.GetOldType() == PINS_DYNAMIC_MATRIX ||
		 p1.GetOldType() == PINS_DYNAMIC_MATRIX))
	{
		int type = std::max(type0, type1);
		SetPinsType(const_cast<bp::Pins&>(p0), type);
		SetPinsType(const_cast<bp::Pins&>(p1), type);
	}
}

void NodeHelper::TypePromote(const bp::Node& node)
{
	bool has_dynamic_vec = false;
	PinsType max_vec = PINS_DYNAMIC_VECTOR;
	bool has_dynamic_mat = false;
	PinsType max_mat = PINS_DYNAMIC_MATRIX;
	for (auto& p : node.GetAllInput())
	{
		auto old_t = p->GetOldType();
		if (old_t == PINS_DYNAMIC_VECTOR) {
			has_dynamic_vec = true;
		}
		if (old_t == PINS_DYNAMIC_MATRIX) {
			has_dynamic_mat = true;
		}

		PinsType t = static_cast<PinsType>(p->GetType());
		if (t >= PINS_DYNAMIC_VECTOR && t <= PINS_VECTOR4) {
			max_vec = std::max(t, max_vec);
		}
		if (t >= PINS_DYNAMIC_MATRIX && t <= PINS_MATRIX4) {
			max_mat = std::max(t, max_mat);
		}
	}
	for (auto& p : node.GetAllOutput())
	{
		auto old_t = p->GetOldType();
		if (old_t == PINS_DYNAMIC_VECTOR) {
			has_dynamic_vec = true;
		}
		if (old_t == PINS_DYNAMIC_MATRIX) {
			has_dynamic_mat = true;
		}

		PinsType t = static_cast<PinsType>(p->GetType());
		if (t >= PINS_DYNAMIC_VECTOR && t <= PINS_VECTOR4) {
			max_vec = std::max(t, max_vec);
		}
		if (t >= PINS_DYNAMIC_MATRIX && t <= PINS_MATRIX4) {
			max_mat = std::max(t, max_mat);
		}
	}

	if (has_dynamic_vec)
	{
		for (auto& p : node.GetAllInput()) {
			if (p->GetOldType() == PINS_DYNAMIC_VECTOR) {
				p->SetType(max_vec);
			}
		}
		for (auto& p : node.GetAllOutput()) {
			if (p->GetOldType() == PINS_DYNAMIC_VECTOR) {
				p->SetType(max_vec);
			}
		}
	}
	if (has_dynamic_mat)
	{
		for (auto& p : node.GetAllInput()) {
			if (p->GetOldType() == PINS_DYNAMIC_MATRIX) {
				p->SetType(max_mat);
			}
		}
		for (auto& p : node.GetAllOutput()) {
			if (p->GetOldType() == PINS_DYNAMIC_MATRIX) {
				p->SetType(max_mat);
			}
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
	auto& parent = pair->GetParent();
	// fixme: is default input param
	if (parent.IsStyleOnlyTitle()) {
		parent.SetLifeDeleteLater(true);
	}
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