#include "shadergraph/node/Exponential.h"

IMPLEMENT_NODE_CLASS(sg::node::Exponential, sg_exp)

namespace sg
{
namespace node
{

void Exponential::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                          rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("type", m_type, alloc);
}

void Exponential::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                           const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("type"));
	SetType(static_cast<BaseType>(val["type"].GetUint()));
}

}
}