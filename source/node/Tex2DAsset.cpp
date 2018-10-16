#include "shadergraph/node/Tex2DAsset.h"

#include <painting2/RenderSystem.h>
#include <facade/Image.h>
#include <facade/ResPool.h>

namespace sg
{
namespace node
{

void Tex2DAsset::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);

	if (m_img)
	{
		auto model_mat = NodePreview::CalcNodePreviewMat(*this, mt);
		pt2::RenderSystem::DrawTexture(*m_img->GetTexture(), model_mat);
	}
}

void Tex2DAsset::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;
}

void Tex2DAsset::SetImagePath(const char* filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(filepath);
}

const char* Tex2DAsset::GetImagePath() const
{
	return m_img ? m_img->GetResPath().c_str() : "";
}

}
}