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

	m_name = val["name"].GetString();
	m_type = static_cast<PinsType>(val["type"].GetInt());
}

}
}