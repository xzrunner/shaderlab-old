#include "shadergraph/Constant3.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace shadergraph
{

const std::string Constant3::TYPE_NAME = "mat_constant3";

Constant3::Constant3()
	: Node("Constant3")
{
	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR3, "Out", *this));

	Layout();

	UpdateTitle();
}

void Constant3::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                        rapidjson::MemoryPoolAllocator<>& alloc) const
{
	val.SetObject();
	val.AddMember("x", m_val.x, alloc);
	val.AddMember("y", m_val.y, alloc);
	val.AddMember("z", m_val.z, alloc);
}

void Constant3::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                         const rapidjson::Value& val)
{
	assert(val.IsObject() && val.HasMember("x") && val.HasMember("y") && val.HasMember("z"));
	float x = val["x"].GetFloat();
	float y = val["y"].GetFloat();
	float z = val["z"].GetFloat();
	SetValue(sm::vec3(x, y, z));
}

sm::vec3 Constant3::ToVec3() const
{
	return m_val;
}

void Constant3::SetValue(const sm::vec3& val)
{
	m_val = val;
	UpdateTitle();
}

void Constant3::UpdateTitle()
{
	m_style.small_title = true;
	m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.y, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.z, 2);
}

}