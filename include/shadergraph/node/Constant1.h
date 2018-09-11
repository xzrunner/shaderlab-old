#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Constant1 : public Node
{
public:
	Constant1();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Constant1>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::Node> Create() const override {
		return std::make_shared<Constant1>();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(float val);

	static const std::string TYPE_NAME;

private:
	void UpdateTitle();

private:
	std::shared_ptr<bp::Pins> m_output;

	float m_val = 0;

}; // Constant1

}
}