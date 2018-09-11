#pragma once

#include "shadergraph/Node.h"

namespace pt3 { class Material; }

namespace sg
{
namespace node
{

class Phong : public Node
{
public:
	Phong();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Phong>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Phong>();
	}

	static const std::string TYPE_NAME;

public:
	enum InputId
	{
		ID_AMBIENT = 0,
		ID_DIFFUSE,
		ID_SPECULAR,
		ID_SHININESS,
		ID_DIFFUSE_TEX,
	};

private:
	std::shared_ptr<bp::Pins> m_ambient;
	std::shared_ptr<bp::Pins> m_diffuse;
	std::shared_ptr<bp::Pins> m_specular;
	std::shared_ptr<bp::Pins> m_shininess;
	std::shared_ptr<bp::Pins> m_diffuse_tex;

}; // Phong

}
}