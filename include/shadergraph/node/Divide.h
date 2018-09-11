#pragma once

#include <blueprint/Node.h>

namespace sg
{
namespace node
{

class Divide : public bp::Node
{
public:
	Divide();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Divide>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Divide>();
	}

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::Pins> m_input0;
	std::shared_ptr<bp::Pins> m_input1;

	std::shared_ptr<bp::Pins> m_output;

}; // Divide

}
}