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
	static const size_t CHANNEL_COUNT = 4;

	enum ChannelType
	{
		CHANNEL_R = 0,
		CHANNEL_G,
		CHANNEL_B,
		CHANNEL_A
	};

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

	auto& GetChannels() const { return m_channels; }
	void SetChannels(const std::array<ChannelType, CHANNEL_COUNT>& channels) {
		m_channels = channels;
	}

private:
	std::array<ChannelType, CHANNEL_COUNT> m_channels
		= { CHANNEL_R, CHANNEL_G, CHANNEL_B, CHANNEL_A };

	RTTR_ENABLE(Node)

}; // Swizzle

}
}