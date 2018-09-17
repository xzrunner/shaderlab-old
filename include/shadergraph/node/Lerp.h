#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Lerp : public Node
{
public:
	Lerp();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Lerp>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Lerp>();
	}

	static const std::string TYPE_NAME;

public:
	enum InputId
	{
		ID_A = 0,
		ID_B,
		ID_T
	};

private:
	std::shared_ptr<bp::Pins> m_a;
	std::shared_ptr<bp::Pins> m_b;
	std::shared_ptr<bp::Pins> m_t;

	std::shared_ptr<bp::Pins> m_output;

}; // Lerp

}
}