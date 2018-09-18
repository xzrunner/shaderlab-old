#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Constant4 : public Node
{
public:
	Constant4()
		: Node("Constant4", false)
	{
		AddPins(std::make_shared<Pins>(false, 0, PINS_VECTOR4, "Out", *this));

		Layout();

		UpdateTitle();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec4& val);

private:
	void UpdateTitle();

private:
	sm::vec4 m_val;

	DECLARE_NODE_CLASS(Constant4)

}; // Constant4

}
}