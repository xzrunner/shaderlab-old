#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class Constant3 : public Node
{
public:
	Constant3();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Constant3>();
	}
	virtual std::string TypeName() const override {
		return "mat_constant3";
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<Constant3>();
	}

	virtual sm::vec3 ToVec3() const override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec3& val);

private:
	void UpdateTitle();

private:
	std::shared_ptr<bp::node::Pins> m_output;

	sm::vec3 m_val;

}; // Constant3

}