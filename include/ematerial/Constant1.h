#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class Constant1 : public Node
{
public:
	Constant1();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Constant1>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<Constant1>();
	}

	virtual sm::vec3 ToVec3() const override;

	auto& GetValue() const { return m_val; }
	void SetValue(float val);

	static const std::string TYPE_NAME;

private:
	void UpdateTitle();

private:
	std::shared_ptr<bp::node::Pins> m_output;

	float m_val = 0;

}; // Constant1

}