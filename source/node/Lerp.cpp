#include "shadergraph/node/Lerp.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/NodeHelper.h"

#include <painting2/RenderSystem.h>

namespace sg
{
namespace node
{

const std::string Lerp::TYPE_NAME = "sg_lerp";

Lerp::Lerp()
	: bp::Node("Lerp")
{
	AddPins(m_a = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "A", *this));
	AddPins(m_b = std::make_shared<Pins>(true, 1, PINS_VECTOR1, "B", *this));
	AddPins(m_t = std::make_shared<Pins>(true, 2, PINS_VECTOR1, "T", *this));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();
}

void Lerp::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);

	auto model_mat = NodeHelper::CalcNodePreviewMat(*this, mt);
	if (m_draw_tex) {
		pt2::RenderSystem::DrawTexture(m_shader, model_mat);
	} else {
		pt2::RenderSystem::DrawColor(m_shader, model_mat);
	}
}

bool Lerp::Update(const bp::UpdateParams& params)
{
	bp::Node::Update(params);

	m_draw_tex = NodeHelper::HasInputTexture(*this);
	if (m_draw_tex) {
		ShaderWeaver sw(ShaderWeaver::VERT_SPRITE, *this);
		m_shader = sw.CreateShader(*params.wc2);
	} else {
		ShaderWeaver sw(ShaderWeaver::VERT_SHAPE, *this);
		m_shader = sw.CreateShader(*params.wc2);
	}

	return true;
}

}
}