#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

class Vector2 : public Node
{
public:
	Vector2()
		: Node("Vector2", false)
	{
		InitPins({
		},{
			{ PINS_VECTOR2, "Out" }
		});

		UpdateTitle();
	}

	virtual void Refresh() override {
		UpdateTitle();
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec2& val) {
		m_val = val;
		UpdateTitle();
	}

	// for serialize with rttr
	float GetX() const { return m_val.x; }
	void SetX(float x) { m_val.x = x; UpdateTitle(); }
	float GetY() const { return m_val.y; }
	void SetY(float y) { m_val.y = y; UpdateTitle(); }

private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.y, 2);
	}

private:
	sm::vec2 m_val;

	RTTR_ENABLE(Node)

}; // Vector2

}
}