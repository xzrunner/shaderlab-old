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
			{ PINS_VECTOR1, "In", }
		},{
			{ PINS_VECTOR1, "Out", }
		});
	}

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