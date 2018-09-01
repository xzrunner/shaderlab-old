#include "ematerial/TextureObject.h"

#include <SM_Rect.h>
#include <painting2/RenderSystem.h>
#include <blueprint/Pins.h>
#include <facade/ResPool.h>
#include <facade/Image.h>

namespace ematerial
{

TextureObject::TextureObject()
	: Node("TextureObject")
{
	AddPins(m_output = std::make_shared<bp::node::Pins>(
		false, 0, bp::node::PINS_OBJECT, "", *this));

	Layout();
}

void TextureObject::SetImage(const std::string& filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(filepath);
}

void TextureObject::Draw(const sm::Matrix2D& mt) const
{
	if (!m_img) {
		return;
	}

	sm::rect r;
	r.xmin = 0; r.xmax = m_img->GetWidth();
	r.ymin = static_cast<float>(-m_img->GetHeight()); r.ymax = 0;
	pt2::RenderSystem::DrawTexture(*m_img->GetTexture(), r, mt);
}

}