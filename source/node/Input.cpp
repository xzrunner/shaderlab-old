#include "shadergraph/node/Input.h"

namespace sg
{
namespace node
{

const std::string Input::TYPE_NAME = "sg_input";

Input::Input()
	: bp::Node("Input")
	, m_type(PINS_VECTOR1)
{
	AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));

	Layout();
}

void Input::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                    rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("name", rapidjson::Value(m_name.c_str(), alloc), alloc);
	val.AddMember("type", m_type, alloc);
}

void Input::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                     const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	SetName(val["name"].GetString());
	SetType(static_cast<PinsType>(val["type"].GetInt()));
}

Input& Input::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;

	return *this;
}

Input& Input::SetType(sg::PinsType type)
{
	m_type = type;
	return *this;
}

}
}