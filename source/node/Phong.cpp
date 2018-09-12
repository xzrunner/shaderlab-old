#include "shadergraph/node/Phong.h"
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

const std::string Phong::TYPE_NAME = "sg_phong";

Phong::Phong()
	: bp::Node("Phong")
{
	AddPins(m_ambient     = std::make_shared<Pins>(true, ID_AMBIENT, PINS_VECTOR3, "Ambient", *this));
	AddPins(m_diffuse     = std::make_shared<Pins>(true, ID_DIFFUSE, PINS_VECTOR3, "Diffuse", *this));
	AddPins(m_specular    = std::make_shared<Pins>(true, ID_SPECULAR, PINS_VECTOR3, "Specular", *this));
	AddPins(m_shininess   = std::make_shared<Pins>(true, ID_SHININESS, PINS_VECTOR1, "Shininess", *this));
	AddPins(m_diffuse_tex = std::make_shared<Pins>(true, ID_DIFFUSE_TEX, PINS_TEXTURE2D, "DiffuseTex", *this));

	Layout();
}

}
}