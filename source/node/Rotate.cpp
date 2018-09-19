#include "shadergraph/node/Rotate.h"

IMPLEMENT_NODE_CLASS(sg::node::Rotate, sg_rotate)

namespace sg
{
namespace node
{

void Rotate::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                     rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("is_radians", m_is_radians, alloc);
}

void Rotate::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                      const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	m_is_radians = val["is_radians"].GetBool();
}

}
}