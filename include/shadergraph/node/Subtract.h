#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Subtract : public Node
{
public:
	Subtract();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Subtract>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Subtract>();
	}

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::Pins> m_input0;
	std::shared_ptr<bp::Pins> m_input1;

	std::shared_ptr<bp::Pins> m_output;

}; // Subtract

}
}