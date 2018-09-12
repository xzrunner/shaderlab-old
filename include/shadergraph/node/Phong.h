#pragma once

#include <blueprint/Node.h>

namespace pt3 { class Material; }

namespace sg
{
namespace node
{

class Phong : public bp::Node
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
		ID_LIT_POSITION = 0,
		ID_LIT_AMBIENT,
		ID_LIT_DIFFUSE,
		ID_LIT_SPECULAR,

		ID_MAT_DIFFUSE,
		ID_MAT_SPECULAR,
		ID_MAT_SHININESS,
		ID_MAT_EMISSION,

		ID_VIEW_POS,
	};

private:
	// light
	std::shared_ptr<bp::Pins> m_lit_position;
	std::shared_ptr<bp::Pins> m_lit_ambient;
	std::shared_ptr<bp::Pins> m_lit_diffuse;
	std::shared_ptr<bp::Pins> m_lit_specular;

	// material
	std::shared_ptr<bp::Pins> m_mat_diffuse;
	std::shared_ptr<bp::Pins> m_mat_specular;
	std::shared_ptr<bp::Pins> m_mat_shininess;
	std::shared_ptr<bp::Pins> m_mat_emission;

	// view
	std::shared_ptr<bp::Pins> m_view_pos;

}; // Phong

}
}