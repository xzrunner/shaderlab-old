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

	virtual void Refresh() override {
		UpdateTitle();
	}

	auto GetValue() const { return m_val; }
	void SetValue(bool val) {
		m_val = val;
		UpdateTitle();
	}

private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = m_val ? "true" : "false";
	}

private:
	bool m_val = true;

	RTTR_ENABLE(Node)

}; // Boolean

}
}