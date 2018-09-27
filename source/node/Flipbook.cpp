#include "shadergraph/node/Flipbook.h"

IMPLEMENT_NODE_CLASS(sg::node::Flipbook, sg_flipbook)

namespace sg
{
namespace node
{

void Flipbook::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                     rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	rapidjson::Value inv_val;
	inv_val.SetArray();
	inv_val.PushBack(m_invert.x, alloc);
	inv_val.PushBack(m_invert.y, alloc);

	val.AddMember("invert", inv_val, alloc);
}

void Flipbook::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                      const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("invert"));
	m_invert.x = val["invert"][0].GetBool();
	m_invert.y = val["invert"][1].GetBool();
}

}
}