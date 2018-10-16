#include "shadergraph/node/InvertColors.h"

namespace sg
{
namespace node
{

void InvertColors::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                           rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("channels", m_channels, alloc);
}

void InvertColors::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                            const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("channels"));
	SetChannels(val["channels"].GetUint());
}

}
}