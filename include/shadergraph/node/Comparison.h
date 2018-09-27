#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Comparison : public Node
{
public:
	Comparison()
		: Node("Comparison", false, true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "A" },
			{ PINS_DYNAMIC_VECTOR, "B" },
		},{
			{ PINS_BOOLEAN, "Out", }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	enum CmpType
	{
		CMP_EQUAL = 0,
		CMP_NOT_EQUAL,
		CMP_LESS,
		CMP_LESS_OR_EQUAL,
		CMP_GREATER,
		CMP_GREATER_OR_EQUAL,
	};

	auto GetCmpType() const { return m_cmp_type; }
	void SetCmpType(CmpType cmp_type) { m_cmp_type = cmp_type; }

	enum InputID
	{
		ID_A = 0,
		ID_B,
	};

	DECLARE_NODE_CLASS(Comparison)

private:
	CmpType m_cmp_type = CMP_EQUAL;

}; // Comparison

}
}