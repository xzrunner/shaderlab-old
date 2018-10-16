#include "shadergraph/node/Tex2DAsset.h"

#include <painting2/RenderSystem.h>
#include <facade/ResPool.h>
#include <facade/Image.h>

#include <boost/filesystem.hpp>

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

void Tex2DAsset::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                            rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("name", rapidjson::Value(m_name.c_str(), alloc), alloc);

	if (!m_img) {
		return;
	}

	std::string relative = boost::filesystem::relative(m_img->GetResPath(), dir).string();
	val.AddMember("filepath", rapidjson::Value(relative.c_str(), alloc), alloc);
}

void Tex2DAsset::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                             const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	SetName(val["name"].GetString());

	if (val.HasMember("filepath"))
	{
		auto filepath = val["filepath"].GetString();
		auto absolute = boost::filesystem::absolute(filepath, dir).string();
		SetImage(absolute);
	}
}

void Tex2DAsset::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;
}

void Tex2DAsset::SetImage(const std::string& filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(filepath);
}

}
}