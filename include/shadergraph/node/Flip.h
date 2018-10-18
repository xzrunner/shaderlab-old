#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

namespace sg
{
namespace node
{

class Flip : public Node
{
public:
	Flip()
		: Node("Flip", true)
		, m_channels(0)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out" },
		});
	}

	auto& GetChannels() const { return m_channels; }
	void SetChannels(const PropMultiChannels& channels) { m_channels = channels; }

private:
	PropMultiChannels m_channels;

	RTTR_ENABLE(Node)

}; // Flip

}
}