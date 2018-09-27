#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Boolean : public Node
{
public:
	Boolean()
		: Node("Boolean", false)
	{
		InitPins({
		},{
			{ PINS_BOOLEAN, "Out" }
		});

		UpdateTitle();
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetValue() const { return m_val; }
	void SetValue(bool val);

private:
	void UpdateTitle();

private:
	bool m_val = true;

	DECLARE_NODE_CLASS(Boolean)

}; // Boolean

}
}