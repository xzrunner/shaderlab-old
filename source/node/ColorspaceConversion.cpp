#include "shadergraph/node/ColorspaceConversion.h"

namespace sg
{
namespace node
{

void ColorspaceConversion::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                                   rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("from", m_from, alloc);
	val.AddMember("to",   m_to, alloc);
}

void ColorspaceConversion::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                                    const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("from") && val.HasMember("to"));
	SetTypes(static_cast<ColorType>(val["from"].GetUint()), static_cast<ColorType>(val["to"].GetUint()));
}

}
}