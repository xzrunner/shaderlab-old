#include "shadergraph/Node.h"
#include "shadergraph/NodePreview.h"
#include "shadergraph/Pins.h"

namespace sg
{

Node::Node(const std::string& title, bool preview, bool debug_print)
	: bp::Node(title)
{
	if (preview) {
		m_preview = std::make_unique<NodePreview>(*this, debug_print);
	}
}

void Node::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);
	if (m_preview) {
		m_preview->Draw(mt);
	}
}

bool Node::Update(const bp::UpdateParams& params)
{
	bool ret = bp::Node::Update(params);
	if (m_preview) {
		if (m_preview->Update(params)) {
			ret = true;
		}
	}
	return ret;
}

void Node::InitPins(const std::vector<PinsDesc>& input,
	                const std::vector<PinsDesc>& output,
	                bool type_static)
{
	InitPinsImpl(input, true);
	InitPinsImpl(output, false);
	Layout();

	if (type_static)
	{
		for (auto& p : GetAllInput()) {
			p->SetTypeStatic(true);
		}
		for (auto& p : GetAllOutput()) {
			p->SetTypeStatic(true);
		}
	}
}

void Node::InitPinsImpl(const std::vector<PinsDesc>& pins, bool is_input)
{
	auto& dst = is_input ? m_all_input : m_all_output;
	dst.clear();
	dst.reserve(pins.size());
	int idx = 0;
	for (auto& d : pins)
	{
		auto p = std::make_shared<Pins>(is_input, idx++, d.type, d.name, *this);
		if (!CheckPinsName(*p, dst)) {
			assert(0);
			return;
		}
		dst.push_back(p);
	}
}

}