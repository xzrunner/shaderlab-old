#include "shadergraph/node/Boolean.h"

namespace sg
{
namespace node
{

void Boolean::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                      rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("val", m_val, alloc);
}

void Boolean::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                       const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("val"));
	SetValue(val["val"].GetBool());
}

void Boolean::SetValue(bool val)
{
	m_val = val;
	UpdateTitle();
}

void Boolean::UpdateTitle()
{
	SetStyleSmallTitleFont(true);
	m_title = m_val ? "true" : "false";
}

}
}