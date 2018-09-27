#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ChannelMask : public Node
{
public:
	ChannelMask()
		: Node("ChannelMask", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In", }
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
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

	DECLARE_NODE_CLASS(ChannelMask)

private:
	uint32_t m_channels = CHANNEL_R | CHANNEL_G | CHANNEL_B | CHANNEL_A;

}; // ChannelMask

}
}