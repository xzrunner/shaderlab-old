#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Matrix2 : public Node
{
public:
	Matrix2()
		: Node("Matrix2", false)
	{
		InitPins({
		},{
			{ PINS_MATRIX2, "Out" }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::mat2& val) { m_val = val; }

private:
	sm::mat2 m_val;

	RTTR_ENABLE(Node)

}; // Matrix2

}
}