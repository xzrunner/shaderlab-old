#include "shadergraph/node/Hue.h"

namespace sg
{
namespace node
{

void Hue::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                  rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("is_radians", m_is_radians, alloc);
}

void Hue::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                   const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	m_is_radians = val["is_radians"].GetBool();
}

}
}