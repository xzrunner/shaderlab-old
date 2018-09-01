#pragma once

#include "ematerial/Node.h"

namespace ematerial
{

class PhongModel : public Node
{
public:
	PhongModel();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<PhongModel>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<PhongModel>();
	}

	auto& GetAmbient() const { return m_ambient; }
	auto& GetDiffuse() const { return m_diffuse; }
	auto& GetSpecular() const { return m_specular; }
	auto& GetShininess() const { return m_shininess; }
	auto& GetDiffuseTex() const { return m_diffuse_tex; }

	static const std::string TYPE_NAME;


private:
	std::shared_ptr<bp::node::Pins> m_ambient;
	std::shared_ptr<bp::node::Pins> m_diffuse;
	std::shared_ptr<bp::node::Pins> m_specular;
	std::shared_ptr<bp::node::Pins> m_shininess;
	std::shared_ptr<bp::node::Pins> m_diffuse_tex;

}; // PhongModel

}