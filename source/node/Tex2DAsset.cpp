#include "shadergraph/node/Tex2DAsset.h"

#include <blueprint/NodeHelper.h>

#include <painting2/RenderSystem.h>
#include <node2/RenderSystem.h>
#include <facade/Image.h>
#include <facade/ResPool.h>

namespace sg
{
namespace node
{

void Tex2DAsset::Draw(const n2::RenderParams& rp) const
{
	bp::Node::Draw(rp);

	if (m_img)
	{
		auto model_mat = bp::NodeHelper::CalcPreviewMat(*this, rp.GetMatrix());
		pt2::RenderSystem::DrawTexture(*m_img->GetTexture(), sm::rect(1, 1), model_mat);
	}
}

void Tex2DAsset::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;
}

void Tex2DAsset::SetImagePath(std::string filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(std::move(filepath));
}

std::string Tex2DAsset::GetImagePath() const
{
	return m_img ? m_img->GetResPath() : "";
}

}
}