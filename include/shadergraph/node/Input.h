//#pragma once
//
//#include "shadergraph/Node.h"
//#include "shadergraph/Pins.h"
//
//namespace sg
//{
//namespace node
//{
//
//class Input : public Node
//{
//public:
//	Input()
//		: Node("Input", false)
//		, m_type(PINS_VECTOR1)
//	{
//		InitPins({
//		},{
//			{ PINS_VECTOR1, "Out" }
//		});
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