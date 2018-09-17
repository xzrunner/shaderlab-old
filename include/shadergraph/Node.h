#pragma once

#include "shadergraph/NodePreview.h"

#include <blueprint/Node.h>

namespace sg
{

class Node : public bp::Node
{
public:
	Node(const std::string& title, bool preview);

	virtual void Draw(const sm::Matrix2D& mt) const override;
	virtual bool Update(const bp::UpdateParams& params) override;

private:
	std::unique_ptr<NodePreview> m_preview = nullptr;

}; // Node

}