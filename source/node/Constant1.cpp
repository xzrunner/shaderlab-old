#include "shadergraph/node/Constant1.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace shadergraph
{
namespace node
{

const std::string Constant1::TYPE_NAME = "sg_constant1";

Constant1::Constant1()
	: Node("Constant1")
{
	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();

	UpdateTitle();
}

void Constant1::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                        rapidjson::MemoryPoolAllocator<>& alloc) const
{
	val.SetObject();
	val.AddMember("x", m_val, alloc);
}

void Constant1::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                         const rapidjson::Value& val)
{
	assert(val.IsObject() && val.HasMember("x"));
	float x = val["x"].GetFloat();
	SetValue(x);
}

sm::vec3 Constant1::ToVec3() const
{
	return sm::vec3(m_val, m_val, m_val);
}

void Constant1::SetValue(float val)
{
	m_val = val;
	UpdateTitle();
}

void Constant1::UpdateTitle()
{
	m_style.small_title = true;
	m_title = cpputil::StringHelper::ToString(m_val, 2);
}

}
}