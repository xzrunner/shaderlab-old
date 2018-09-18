//#include "shadergraph/node/Input.h"
//
//IMPLEMENT_NODE_CLASS(sg::node::Input, sg_input)
//
//namespace sg
//{
//namespace node
//{
//
//void Input::StoreToJson(const std::string& dir, rapidjson::Value& val,
//	                    rapidjson::MemoryPoolAllocator<>& alloc) const
//{
//	bp::Node::StoreToJson(dir, val, alloc);
//
//	val.AddMember("name", rapidjson::Value(m_name.c_str(), alloc), alloc);
//	val.AddMember("type", m_type, alloc);
//}
//
//void Input::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
//	                     const rapidjson::Value& val)
//{
//	bp::Node::LoadFromJson(alloc, dir, val);
//
//	SetName(val["name"].GetString());
//	SetType(static_cast<PinsType>(val["type"].GetInt()));
//}
//
//Input& Input::SetName(const std::string& name)
//{
//	m_name = name;
//	m_title = m_name;
//
//	return *this;
//}
//
//Input& Input::SetType(sg::PinsType type)
//{
//	m_type = type;
//	return *this;
//}
//
//}
//}