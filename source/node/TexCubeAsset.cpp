#include "shadergraph/node/TexCubeAsset.h"

#include <painting2/RenderSystem.h>
#include <node2/RenderSystem.h>
#include <facade/ImageCube.h>
#include <facade/ResPool.h>

namespace sg
{
namespace node
{

void TexCubeAsset::Draw(const ur2::Device& dev, ur2::Context& ctx,
                        const n2::RenderParams& rp) const
{
	bp::Node::Draw(dev, ctx, rp);
}

void TexCubeAsset::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;
}

void TexCubeAsset::SetImagePath(std::string filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::ImageCube>(std::move(filepath), nullptr);
}

std::string TexCubeAsset::GetImagePath() const
{
	return m_img ? m_img->GetResPath() : "";
}

}
}