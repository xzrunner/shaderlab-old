#include "ematerial/PhongModel.h"

#include <blueprint/Pins.h>

namespace ematerial
{

PhongModel::PhongModel()
	: Node("PhongModel")
{
	AddPins(m_ambient = std::make_shared<bp::node::Pins>(
		true, 0, bp::node::PINS_VECTOR, "ambient", *this));
	AddPins(m_diffuse = std::make_shared<bp::node::Pins>(
		true, 1, bp::node::PINS_VECTOR, "diffuse", *this));
	AddPins(m_specular = std::make_shared<bp::node::Pins>(
		true, 2, bp::node::PINS_VECTOR, "specular", *this));
	AddPins(m_shininess = std::make_shared<bp::node::Pins>(
		true, 3, bp::node::PINS_FLOAT, "shininess", *this));
	AddPins(m_diffuse_tex = std::make_shared<bp::node::Pins>(
		true, 4, bp::node::PINS_OBJECT, "diffuse_tex", *this));

	Layout();
}

}