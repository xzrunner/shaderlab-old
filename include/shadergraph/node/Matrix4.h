#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Matrix4 : public Node
{
public:
	Matrix4()
		: Node("Matrix4", false)
	{
		InitPins({
		},{
			{ PINS_MATRIX4, "Out" }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::mat4& val) { m_val = val; }

private:
	sm::mat3 m_val;

	DECLARE_NODE_CLASS(Matrix4)

}; // Matrix4

}
}