#include "shadergraph/node/TextureSample.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/NodeHelper.h"

#include <painting2/RenderSystem.h>

namespace sg
{
namespace node
{

const std::string TextureSample::TYPE_NAME = "sg_tex_sample";

TextureSample::TextureSample()
	: bp::Node("TextureSample")
{
	AddPins(m_tex = std::make_shared<Pins>(true, 0, PINS_TEXTURE2D, "Tex", *this));
	AddPins(m_uv  = std::make_shared<Pins>(true, 1, PINS_VECTOR2,   "UV", *this));

	AddPins(m_rgba = std::make_shared<Pins>(false, 0, PINS_VECTOR4, "RGBA", *this));
	AddPins(m_r    = std::make_shared<Pins>(false, 1, PINS_VECTOR1, "R", *this));
	AddPins(m_g    = std::make_shared<Pins>(false, 2, PINS_VECTOR1, "G", *this));
	AddPins(m_b    = std::make_shared<Pins>(false, 3, PINS_VECTOR1, "B", *this));
	AddPins(m_a    = std::make_shared<Pins>(false, 4, PINS_VECTOR1, "A", *this));

	Layout();
}


void TextureSample::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);

	auto model_mat = NodeHelper::CalcNodePreviewMat(*this, mt);
	pt2::RenderSystem::DrawTexture(m_shader, model_mat);
}

bool TextureSample::Update(const bp::UpdateParams& params)
{
	bp::Node::Update(params);

	ShaderWeaver sw(ShaderWeaver::VERT_SPRITE, *this);
	m_shader = sw.CreateShader(*params.wc2);

	return true;
}

}
}