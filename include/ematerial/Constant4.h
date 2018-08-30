#pragma once

#include <blueprint/Node.h>

namespace ematerial
{

class Constant4 : public bp::node::Node
{
public:
	Constant4();

	virtual bp::NodeTypeID  TypeID() const override {
		return bp::GetNodeTypeID<Constant4>();
	}
	virtual std::string TypeName() const override {
		return "bp_constant4";
	}
	virtual std::shared_ptr<Node> Create() const override {
		return std::make_shared<Constant4>();
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec4& val) { m_val = val; }

private:
	std::shared_ptr<bp::node::Pins> m_output;

	sm::vec4 m_val;

}; // Constant4

}