#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Swizzle : public Node
{
public:
	Swizzle()
		: Node("Swizzle", true)
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

	void GetChannels(uint32_t channels[4]) const {
		memcpy(channels, m_channels, sizeof(m_channels));
	}
	void SetChannels(uint32_t channels[4]) {
		memcpy(m_channels, channels, sizeof(m_channels));
	}

	enum ChannelType
	{
		CHANNEL_R = 0,
		CHANNEL_G,
		CHANNEL_B,
		CHANNEL_A
	};

	DECLARE_NODE_CLASS(Swizzle)

private:
	ChannelType m_channels[4] = { CHANNEL_R, CHANNEL_G, CHANNEL_B, CHANNEL_A };

}; // Swizzle

}
}