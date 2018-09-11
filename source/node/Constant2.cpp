#include "shadergraph/node/Constant2.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

const std::string Constant2::TYPE_NAME = "sg_constant2";

Constant2::Constant2()
	: Node("Constant2")
{
	AddPins(m_output = std::make_shared<Pins>(false, 0, PINS_VECTOR2, "Out", *this));

	Layout();

	UpdateTitle();
}

void Constant2::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                        rapidjson::MemoryPoolAllocator<>& alloc) const
{
	val.SetObject();
	val.AddMember("x", m_val.x, alloc);
	val.AddMember("y", m_val.y, alloc);
}

void Constant2::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                         const rapidjson::Value& val)
{
	assert(val.IsObject() && val.HasMember("x") && val.HasMember("y"));
	float x = val["x"].GetFloat();
	float y = val["y"].GetFloat();
	SetValue(sm::vec2(x, y));
}

void Constant2::SetValue(const sm::vec2& val)
{
	m_val = val;
	UpdateTitle();
}

void Constant2::UpdateTitle()
{
	SetStyleSmallTitleFont(true);
	m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
		      cpputil::StringHelper::ToString(m_val.y, 2);
}

}
}