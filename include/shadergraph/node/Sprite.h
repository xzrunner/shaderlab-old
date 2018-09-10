#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Sprite : public Node
{
public:
	Sprite();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Sprite>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::Node> Create() const override {
		return std::make_shared<Sprite>();
	}

	static const std::string TYPE_NAME;

public:
	enum InputId
	{
		ID_TEX = 0,
		ID_COL_MUL,
		ID_COL_ADD,
	};

private:
	std::shared_ptr<bp::Pins> m_tex;
	std::shared_ptr<bp::Pins> m_col_mul;
	std::shared_ptr<bp::Pins> m_col_add;

}; // Sprite

}
}