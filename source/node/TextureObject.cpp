#include "shadergraph/node/TextureObject.h"
#include "shadergraph/Pins.h"

#include <SM_Rect.h>
#include <painting2/RenderSystem.h>
#include <facade/ResPool.h>
#include <facade/Image.h>

#include <boost/filesystem.hpp>

namespace sg
{
namespace node
{

const std::string TextureObject::TYPE_NAME = "sg_tex_obj";

TextureObject::TextureObject()
	: bp::Node("TextureObject")
	, m_name("tex")
{
	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_TEXTURE2D, "Tex", *this));

	Layout();
}

void TextureObject::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);

	DrawImage(mt);
}

void TextureObject::StoreToJson(const std::string& dir, rapidjson::Value& val,
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

void TextureObject::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
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

void TextureObject::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;
}

void TextureObject::SetImage(const std::string& filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(filepath);
}

void TextureObject::DrawImage(const sm::Matrix2D& mt) const
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

}
}