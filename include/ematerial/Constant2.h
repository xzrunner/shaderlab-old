#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class Constant2 : public Node
{
public:
	Constant2();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Constant2>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<Constant2>();
	}

	virtual sm::vec3 ToVec3() const override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec2& val);

	static const std::string TYPE_NAME;

private:
	void UpdateTitle();

private:
	std::shared_ptr<bp::node::Pins> m_output;

	sm::vec2 m_val;

}; // Constant2

}