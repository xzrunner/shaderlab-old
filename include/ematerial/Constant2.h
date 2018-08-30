#pragma once

#include <blueprint/Node.h>

namespace ematerial
{

class Constant2 : public bp::node::Node
{
public:
	Constant2();

	virtual bp::NodeTypeID  TypeID() const override {
		return bp::GetNodeTypeID<Constant2>();
	}
	virtual std::string TypeName() const override {
		return "mat_constant2";
	}
	virtual std::shared_ptr<Node> Create() const override {
		return std::make_shared<Constant2>();
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec2& val) { m_val = val; }

private:
	std::shared_ptr<bp::node::Pins> m_output;

	sm::vec2 m_val;

}; // Constant2

}