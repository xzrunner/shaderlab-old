#include "shadergraph/node/ChannelMask.h"

namespace sg
{
namespace node
{

void ChannelMask::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                          rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("channels", m_channels, alloc);
}

void ChannelMask::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                           const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("channels"));
	SetChannels(val["channels"].GetUint());
}

}
}