#include "shadergraph/node/Vector2.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

void Vector2::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                        rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("x", m_val.x, alloc);
	val.AddMember("y", m_val.y, alloc);
}

void Vector2::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                         const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("x") && val.HasMember("y"));
	float x = val["x"].GetFloat();
	float y = val["y"].GetFloat();
	SetValue(sm::vec2(x, y));
}

void Vector2::SetValue(const sm::vec2& val)
{
	m_val = val;
	UpdateTitle();
}

void Vector2::UpdateTitle()
{
	SetStyleSmallTitleFont(true);
	m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.y, 2);
}

}
}