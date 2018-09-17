#include "shadergraph/node/Remap.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/NodeHelper.h"

#include <painting2/RenderSystem.h>

namespace sg
{
namespace node
{

const std::string Remap::TYPE_NAME = "sg_remap";

Remap::Remap()
	: bp::Node("Remap")
{
	AddPins(m_in   = std::make_shared<Pins>(true, 0, PINS_VECTOR1, "In",   *this));
	AddPins(m_from = std::make_shared<Pins>(true, 1, PINS_VECTOR2, "From", *this));
	AddPins(m_to   = std::make_shared<Pins>(true, 2, PINS_VECTOR2, "To",   *this));

	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	m_from->SetTypeStatic(true);
	m_to->SetTypeStatic(true);

	Layout();
}

void Remap::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);

	auto model_mat = NodeHelper::CalcNodePreviewMat(*this, mt);
	if (m_draw_tex) {
		pt2::RenderSystem::DrawTexture(m_shader, model_mat);
	} else {
		pt2::RenderSystem::DrawColor(m_shader, model_mat);
	}
}

bool Remap::Update(const bp::UpdateParams& params)
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