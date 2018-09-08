#include "shadergraph/node/TextureObject.h"
#include "shadergraph/Pins.h"

#include <SM_Rect.h>
#include <painting2/RenderSystem.h>
#include <facade/ResPool.h>
#include <facade/Image.h>

#include <boost/filesystem.hpp>

namespace shadergraph
{
namespace node
{

const std::string TextureObject::TYPE_NAME = "sg_tex_obj";

TextureObject::TextureObject()
	: Node("TextureObject")
{
	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_TEXTURE2D, "Tex", *this));

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

void TextureObject::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                            rapidjson::MemoryPoolAllocator<>& alloc) const
{
	if (!m_img) {
		return;
	}

	val.SetObject();

	std::string relative = boost::filesystem::relative(m_img->GetResPath(), dir).string();
	val.AddMember("filepath", rapidjson::Value(relative.c_str(), alloc), alloc);
}

void TextureObject::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                             const rapidjson::Value& val)
{
	if (val.IsObject() && val.HasMember("filepath"))
	{
		auto filepath = val["filepath"].GetString();
		auto absolute = boost::filesystem::absolute(filepath, dir).string();
		SetImage(absolute);
	}
}

void TextureObject::SetImage(const std::string& filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(filepath);
}

}
}