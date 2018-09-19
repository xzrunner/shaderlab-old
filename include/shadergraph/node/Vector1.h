#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Vector1 : public Node
{
public:
	Vector1()
		: Node("Vector1", false)
	{
		InitPins({
		},{
			{ PINS_VECTOR1, "Out" }
		});

		UpdateTitle();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(float val);

private:
	void UpdateTitle();

private:
	float m_val = 0;

	DECLARE_NODE_CLASS(Vector1)

}; // Vector1

}
}