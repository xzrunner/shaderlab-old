#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class Constant4 : public Node
{
public:
	Constant4();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Constant4>();
	}
	virtual std::string TypeName() const override {
		return "mat_constant4";
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<Constant4>();
	}

	virtual sm::vec3 ToVec3() const override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec4& val);

private:
	void UpdateTitle();

private:
	std::shared_ptr<bp::node::Pins> m_output;

	sm::vec4 m_val;

}; // Constant4

}