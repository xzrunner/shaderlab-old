#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Vector3 : public Node
{
public:
	Vector3()
		: Node("Vector3", false)
	{
		InitPins({
		},{
			{ PINS_VECTOR3, "Out" }
		});

		UpdateTitle();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec3& val);

private:
	void UpdateTitle();

private:
	sm::vec3 m_val;

	DECLARE_NODE_CLASS(Vector3)

}; // Vector3

}
}