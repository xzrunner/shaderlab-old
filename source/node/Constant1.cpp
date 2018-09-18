#include "shadergraph/node/Constant1.h"

#include <cpputil/StringHelper.h>

IMPLEMENT_NODE_CLASS(sg::node::Constant1, sg_constant1)

namespace sg
{
namespace node
{

void Constant1::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                        rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("x", m_val, alloc);
}

void Constant1::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                         const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("x"));
	float x = val["x"].GetFloat();
	SetValue(x);
}

void Constant1::SetValue(float val)
{
	m_val = val;
	UpdateTitle();
}

void Constant1::UpdateTitle()
{
	SetStyleSmallTitleFont(true);
	m_title = cpputil::StringHelper::ToString(m_val, 2);
}

}
}