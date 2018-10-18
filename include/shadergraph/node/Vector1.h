#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

class Vector1 : public Node
{
public:
	Vector1()
		: Node("Vector1", false)
	{
		InitPins({
		},{
			{ PINS_VECTOR1, "Out" }
		});

		UpdateTitle();
	}

	virtual void Refresh() override {
		UpdateTitle();
	}

	auto GetValue() const { return m_val; }
	void SetValue(float val) {
		m_val = val;
		UpdateTitle();
	}

private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val, 2);
	}

private:
	float m_val = 0;

	RTTR_ENABLE(Node)

}; // Vector1

}
}