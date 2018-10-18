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

	auto& GetChannels() const { return m_channels; }
	void SetChannels(const PropChannelArray& channels) {
		m_channels = channels;
	}

private:
	PropChannelArray m_channels;

	RTTR_ENABLE(Node)

}; // Swizzle

}
}