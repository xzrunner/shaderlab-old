#pragma once

#include "shadergraph/NodePreview.h"

#include <blueprint/Node.h>

namespace sg
{

class Node : public bp::Node
{
public:
	Node(const std::string& title, bool preview,
		bool debug_print = false, bool use_rt = false);

	virtual void Draw(const sm::Matrix2D& mt) const override;
	virtual bool Update(const bp::UpdateParams& params) override;

	struct PinsDesc
	{
		int         type;
		std::string name;
	};

protected:
	void InitPins(const std::vector<PinsDesc>& input,
		const std::vector<PinsDesc>& output);
	void InitPins(const std::string& name);

	void InitPinsImpl(const std::vector<PinsDesc>& pins,
		bool is_input);

private:
	static std::string PortNameFromVar(const std::string& str);

private:
	std::unique_ptr<NodePreview> m_preview = nullptr;

	RTTR_ENABLE(bp::Node)

}; // Node

}