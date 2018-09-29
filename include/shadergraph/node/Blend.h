#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

#include <shaderweaver/node/Blend.h>

namespace sg
{
namespace node
{

class Blend : public Node
{
public:
	Blend()
		: Node("Blend", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "Base" },
			{ PINS_DYNAMIC_VECTOR, "Blend" },
			{ PINS_VECTOR1,        "Opacity" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto GetMode() const { return m_mode; }
	void SetMode(sw::node::Blend::ModeType mode) { m_mode = mode; }

	enum InputID
	{
		ID_BASE = 0,
		ID_BLEND,
		ID_OPACITY,
	};

	DECLARE_NODE_CLASS(Blend)

private:
	sw::node::Blend::ModeType m_mode = sw::node::Blend::MODE_BURN;

}; // Blend

}
}