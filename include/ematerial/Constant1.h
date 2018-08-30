#pragma once

#include <blueprint/Node.h>

namespace ematerial
{

class Constant1 : public bp::node::Node
{
public:
	Constant1();

	virtual bp::NodeTypeID  TypeID() const override {
		return bp::GetNodeTypeID<Constant1>();
	}
	virtual std::string TypeName() const override {
		return "mat_constant1";
	}
	virtual std::shared_ptr<Node> Create() const override {
		return std::make_shared<Constant1>();
	}

	auto& GetValue() const { return m_val; }
	void SetValue(float val) { m_val = val; }

private:
	std::shared_ptr<bp::node::Pins> m_output;

	float m_val = 0;

}; // Constant1

}