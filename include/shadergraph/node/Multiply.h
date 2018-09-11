#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Multiply : public Node
{
public:
	Multiply();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Multiply>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Multiply>();
	}

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::Pins> m_input0;
	std::shared_ptr<bp::Pins> m_input1;

	std::shared_ptr<bp::Pins> m_output;

}; // Multiply

}
}