#include "shadergraph/node/Vector4.h"

#include <cpputil/StringHelper.h>

IMPLEMENT_NODE_CLASS(sg::node::Vector4, sg_vec4)

namespace sg
{
namespace node
{

void Vector4::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                        rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("x", m_val.x, alloc);
	val.AddMember("y", m_val.y, alloc);
	val.AddMember("z", m_val.z, alloc);
	val.AddMember("w", m_val.w, alloc);
}

void Vector4::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                         const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("x") && val.HasMember("y") && val.HasMember("z"));
	float x = val["x"].GetFloat();
	float y = val["y"].GetFloat();
	float z = val["z"].GetFloat();
	float w = val["w"].GetFloat();
	SetValue(sm::vec4(x, y, z, w));
}

void Vector4::SetValue(const sm::vec4& val)
{
	m_val = val;
	UpdateTitle();
}

void Vector4::UpdateTitle()
{
	SetStyleSmallTitleFont(true);
	m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.y, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.z, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.w, 2);
}

}
}