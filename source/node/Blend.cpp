#include "shadergraph/node/Blend.h"

namespace sg
{
namespace node
{

void Blend::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                    rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("mode", m_mode, alloc);
}

void Blend::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                     const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("mode"));
	SetMode(static_cast<sw::node::Blend::ModeType>(val["mode"].GetUint()));
}

}
}