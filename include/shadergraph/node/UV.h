#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class UV : public Node
{
public:
	UV();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<UV>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<UV>();
	}

	static const std::string TYPE_NAME;

private:
	// todo
	// int m_channel;

	std::shared_ptr<bp::Pins> m_output;

}; // UV

}
}