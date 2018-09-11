#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Constant2 : public Node
{
public:
	Constant2();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Constant2>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Constant2>();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec2& val);

	static const std::string TYPE_NAME;

private:
	void UpdateTitle();

private:
	std::shared_ptr<bp::Pins> m_output;

	sm::vec2 m_val;

}; // Constant2

}
}