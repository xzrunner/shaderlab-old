#pragma once

#include "shadergraph/NodePreview.h"

#include <blueprint/Node.h>

namespace sg
{

class Node : public bp::Node
{
public:
	Node(const std::string& title, bool preview,
		bool debug_print = false);

	virtual void Draw(const sm::Matrix2D& mt) const override;
	virtual bool Update(const bp::UpdateParams& params) override;

protected:
	struct PinsDesc
	{
		int         type;
		std::string name;
	};
	void InitPins(const std::vector<PinsDesc>& input,
		const std::vector<PinsDesc>& output);

private:
	void InitPinsImpl(const std::vector<PinsDesc>& pins,
		bool is_input);

private:
	std::unique_ptr<NodePreview> m_preview = nullptr;

}; // Node

}