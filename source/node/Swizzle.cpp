#include "shadergraph/node/Swizzle.h"

IMPLEMENT_NODE_CLASS(sg::node::Swizzle, sg_swizzle)

namespace sg
{
namespace node
{

void Swizzle::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                      rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	rapidjson::Value channels_val;
	channels_val.SetArray();
	for (auto& c : m_channels) {
		channels_val.PushBack(c, alloc);
	}
	val.AddMember("channels", channels_val, alloc);
}

void Swizzle::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                       const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("channels"));
	auto& channels_val = val["channels"];
	assert(channels_val.IsArray());
	for (int i = 0; i < 4; ++i) {
		m_channels[i] = static_cast<ChannelType>(channels_val[i].GetInt());
	}
}

}
}