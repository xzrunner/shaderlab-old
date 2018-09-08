#pragma once

#include "shadergraph/Node.h"

namespace shadergraph
{
namespace node
{

class Divide : public Node
{
public:
	Divide();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Divide>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::Node> Create() const override {
		return std::make_shared<Divide>();
	}

	virtual sm::vec3 ToVec3() const override;

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::Pins> m_input0;
	std::shared_ptr<bp::Pins> m_input1;

	std::shared_ptr<bp::Pins> m_output;

}; // Divide

}
}