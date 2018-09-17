#include "shadergraph/NodeHelper.h"
#include "shadergraph/Pins.h"

#include "shadergraph/node/Add.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Divide.h"
#include "shadergraph/node/TextureObject.h"

#include <blueprint/Pins.h>
#include <blueprint/Node.h>
#include <blueprint/Connecting.h>

#include <SM_Rect.h>

#include <algorithm>
#include <queue>

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

bool NodeHelper::HasInputTexture(const bp::Node& node)
{
	bool input_tex = false;

	auto& src_inputs = node.GetAllInput();
	std::queue<std::shared_ptr<bp::Pins>> inputs;
	for (auto& src : src_inputs) {
		inputs.push(src);
	}
	while (!inputs.empty())
	{
		auto input = inputs.front(); inputs.pop();
		auto& conns = input->GetConnecting();
		if (conns.empty()) {
			continue;
		}
		assert(conns.size() == 1);

		auto& node = conns[0]->GetFrom()->GetParent();
		if (node.TypeID() == bp::GetNodeTypeID<node::TextureObject>())
		{
			input_tex = true;
			auto& tex_obj = static_cast<const node::TextureObject&>(node);
			auto& img = tex_obj.GetImage();
			if (img) {
				continue;
			}
		}

		for (auto& from : node.GetAllInput()) {
			inputs.push(from);
		}
	}

	return input_tex;
}

sm::mat4 NodeHelper::CalcNodePreviewMat(const bp::Node& node, const sm::Matrix2D& mt)
{
	auto& style = node.GetStyle();

	const float LEN = style.width;
	sm::rect r;
	r.xmin = -style.width * 0.5f; r.xmax = r.xmin + LEN;
	r.ymax = -style.height * 0.5f; r.ymin = r.ymax - LEN;

	sm::mat4 model_mat;
	model_mat.x[0] = mt.x[0] * r.Width();
	model_mat.x[1] = mt.x[1];
	model_mat.x[4] = mt.x[2];
	model_mat.x[5] = mt.x[3] * r.Height();
	model_mat.x[12] = mt.x[4] + r.Center().x;
	model_mat.x[13] = mt.x[5] + r.Center().y;

	return model_mat;
}

void NodeHelper::SetPinsType(bp::Pins& pins, int type)
{
	if (pins.IsTypeStatic() || pins.GetType() == type) {
		return;
	}

	pins.SetType(type);
	for (auto& conn : pins.GetConnecting()) {
		conn->UpdateCurve();
	}
}

}