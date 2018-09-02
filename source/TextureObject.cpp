#include "shadergraph/TextureObject.h"
#include "shadergraph/PinsType.h"

#include <SM_Rect.h>
#include <painting2/RenderSystem.h>
#include <blueprint/Pins.h>
#include <facade/ResPool.h>
#include <facade/Image.h>

namespace shadergraph
{

const std::string TextureObject::TYPE_NAME = "mat_tex_obj";

TextureObject::TextureObject()
	: Node("TextureObject")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, PINS_TEXTURE2D, "", *this));

	Layout();
}

void TextureObject::Draw(const sm::Matrix2D& mt) const
{
	if (!m_img) {
		return;
	}

	const float LEN = m_style.width;

	sm::rect r;
	r.xmin = -m_style.width * 0.5f; r.xmax = r.xmin + LEN;
	r.ymax = -m_style.height * 0.5f; r.ymin = r.ymax - LEN;
	pt2::RenderSystem::DrawTexture(*m_img->GetTexture(), r, mt);
}

void TextureObject::SetImage(const std::string& filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(filepath);
}

}