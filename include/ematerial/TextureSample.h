#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class TextureSample : public Node
{
public:
	TextureSample();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<TextureSample>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<TextureSample>();
	}

	static const std::string TYPE_NAME;

private:
	// input
	std::shared_ptr<bp::node::Pins> m_tex;
	std::shared_ptr<bp::node::Pins> m_uv;

	// output
	std::shared_ptr<bp::node::Pins> m_rgba;
	std::shared_ptr<bp::node::Pins> m_r;
	std::shared_ptr<bp::node::Pins> m_g;
	std::shared_ptr<bp::node::Pins> m_b;
	std::shared_ptr<bp::node::Pins> m_a;

}; // TextureSample

}