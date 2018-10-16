#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Matrix3 : public Node
{
public:
	Matrix3()
		: Node("Matrix3", false)
	{
		InitPins({
		},{
			{ PINS_MATRIX3, "Out" }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::mat3& val) { m_val = val; }

private:
	sm::mat3 m_val;

	RTTR_ENABLE(Node)

}; // Matrix3

}
}