#include "shadergraph/Node.h"
#include "shadergraph/NodePreview.h"

namespace sg
{

Node::Node(const std::string& title, bool preview)
	: bp::Node(title)
{
	if (preview) {
		m_preview = std::make_unique<NodePreview>(*this);
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

}