#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Exponential : public Node
{
public:
	enum BaseType
	{
		BASE_E = 0,
		BASE_2,
	};

public:
	Exponential()
		: Node("Exponential", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	BaseType GetType() const { return m_type; }
	void SetType(BaseType type) { m_type = type; }

private:
	BaseType m_type = BASE_E;

	RTTR_ENABLE(Node)

}; // Exponential

}
}