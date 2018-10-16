#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

class Vector3 : public Node
{
public:
	Vector3()
		: Node("Vector3", false)
	{
		InitPins({
		},{
			{ PINS_VECTOR3, "Out" }
		});

		UpdateTitle();
	}

	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec3& val) {
		m_val = val;
		UpdateTitle();
	}

	// for serialize
	float GetX() const { return m_val.x; }
	void  SetX(float x) { m_val.x = x; UpdateTitle(); }
	float GetY() const { return m_val.y; }
	void  SetY(float y) { m_val.y = y; UpdateTitle(); }
	float GetZ() const { return m_val.z; }
	void  SetZ(float z) { m_val.z = z; UpdateTitle(); }

private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.y, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.z, 2);
	}

private:
	sm::vec3 m_val;

	RTTR_ENABLE(Node)

}; // Vector3

}
}