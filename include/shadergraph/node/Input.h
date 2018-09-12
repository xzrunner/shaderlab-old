#pragma once

#include "shadergraph/Pins.h"

#include <blueprint/Node.h>

namespace sg
{
namespace node
{

class Input : public bp::Node
{
public:
	Input();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Input>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Input>();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	Input& SetName(const std::string& name);
	auto& GetName() const { return m_name; }

	Input& SetType(sg::PinsType type);
	sg::PinsType GetType() const { return m_type; }

	static const std::string TYPE_NAME;

private:
	std::string m_name;

	sg::PinsType m_type;

}; // Input

}
}