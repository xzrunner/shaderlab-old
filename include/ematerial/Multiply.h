#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class Multiply : public Node
{
public:
	Multiply();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Multiply>();
	}
	virtual std::string TypeName() const override {
		return "mat_mul";
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<Multiply>();
	}

	virtual sm::vec3 ToVec3() const override;

private:
	std::shared_ptr<bp::node::Pins> m_input0;
	std::shared_ptr<bp::node::Pins> m_input1;

	std::shared_ptr<bp::node::Pins> m_output;

}; // Multiply

}