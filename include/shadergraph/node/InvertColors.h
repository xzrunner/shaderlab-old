#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class InvertColors : public Node
{
public:
	InvertColors()
		: Node("InvertColors", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	uint32_t GetChannels() const { return m_channels; }
	void SetChannels(uint32_t channels) { m_channels = channels; }

	static const uint32_t CHANNEL_R = 0x1;
	static const uint32_t CHANNEL_G = 0x2;
	static const uint32_t CHANNEL_B = 0x4;
	static const uint32_t CHANNEL_A = 0x8;

private:
	uint32_t m_channels = 0;

	RTTR_ENABLE(Node)

}; // InvertColors

}
}