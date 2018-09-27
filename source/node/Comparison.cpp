#include "shadergraph/node/Comparison.h"

IMPLEMENT_NODE_CLASS(sg::node::Comparison, sg_comparison)

namespace sg
{
namespace node
{

void Comparison::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                         rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("cmp", m_cmp_type, alloc);
}

void Comparison::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                          const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("cmp"));
	SetCmpType(static_cast<CmpType>(val["cmp"].GetUint()));
}

}
}