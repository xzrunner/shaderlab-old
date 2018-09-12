#include "shadergraph/node/Phong2.h"
#include "shadergraph/node/TextureObject.h"
#include "shadergraph/Pins.h"

#include <blueprint/Connecting.h>
#include <painting2/Texture.h>
#include <painting3/Material.h>
#include <facade/Image.h>

namespace sg
{
namespace node
{

const std::string Phong2::TYPE_NAME = "sg_phong2";

Phong2::Phong2()
	: bp::Node("Phong2")
{
	AddPins(m_lit_position  = std::make_shared<Pins>(true, ID_LIT_POSITION,  PINS_VECTOR3, "Light Position", *this));
	AddPins(m_lit_ambient   = std::make_shared<Pins>(true, ID_LIT_AMBIENT,   PINS_VECTOR3, "Light Ambient", *this));
	AddPins(m_lit_diffuse   = std::make_shared<Pins>(true, ID_LIT_DIFFUSE,   PINS_VECTOR3, "Light Diffuse", *this));
	AddPins(m_lit_specular  = std::make_shared<Pins>(true, ID_LIT_SPECULAR,  PINS_VECTOR3, "Light Specular", *this));

	AddPins(m_mat_diffuse   = std::make_shared<Pins>(true, ID_MAT_DIFFUSE,   PINS_VECTOR3, "Material Diffuse", *this));
	AddPins(m_mat_specular  = std::make_shared<Pins>(true, ID_MAT_SPECULAR,  PINS_VECTOR3, "Material Specular", *this));
	AddPins(m_mat_shininess = std::make_shared<Pins>(true, ID_MAT_SHININESS, PINS_VECTOR1, "Material Shininess", *this));
	AddPins(m_mat_emission  = std::make_shared<Pins>(true, ID_MAT_EMISSION,  PINS_VECTOR3, "Material Emission", *this));

	AddPins(m_view_pos      = std::make_shared<Pins>(true, ID_VIEW_POS,      PINS_VECTOR3, "View pos", *this));

	Layout();
}

}
}