#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Add : public Node
{
public:
	Add();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Add>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::Node> Create() const override {
		return std::make_shared<Add>();
	}

	virtual sm::vec3 ToVec3() const override;

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::Pins> m_input0;
	std::shared_ptr<bp::Pins> m_input1;

	std::shared_ptr<bp::Pins> m_output;

}; // Add

}
}