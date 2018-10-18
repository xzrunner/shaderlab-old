#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class ChannelMask : public Node
{
public:
	ChannelMask()
		: Node("ChannelMask", true)
		, m_channels(
			PropMultiChannels::CHANNEL_R |
			PropMultiChannels::CHANNEL_G |
			PropMultiChannels::CHANNEL_B |
			PropMultiChannels::CHANNEL_A
		)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In", }
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	auto& GetChannels() const { return m_channels; }
	void SetChannels(const PropMultiChannels& channels) { m_channels = channels; }

private:
	PropMultiChannels m_channels;

	RTTR_ENABLE(Node)

}; // ChannelMask

}
}