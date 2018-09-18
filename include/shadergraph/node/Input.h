//#pragma once
//
//#include "shadergraph/Pins.h"
//#include "shadergraph/Pins.h"
//
//#include <blueprint/Node.h>
//
//namespace sg
//{
//namespace node
//{
//
//class Input : public bp::Node
//{
//public:
//	Input()
//		: bp::Node("Input")
//		, m_type(PINS_VECTOR1)
//	{
//		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR1, "Out", *this));
//
//		Layout();
//	}
//
//	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
//		rapidjson::MemoryPoolAllocator<>& alloc) const override;
//	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
//		const rapidjson::Value& val) override;
//
//	Input& SetName(const std::string& name);
//	auto& GetName() const { return m_name; }
//
//	Input& SetType(sg::PinsType type);
//	sg::PinsType GetType() const { return m_type; }
//
//private:
//	std::string m_name;
//
//	sg::PinsType m_type;
//
//	DECLARE_NODE_CLASS(Input)
//
//}; // Input
//
//}
//}