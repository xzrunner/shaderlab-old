#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class ColorspaceConversion : public Node
{
public:
	ColorspaceConversion()
		: Node("ColorspaceConversion", true)
	{
		InitPins({
			{ PINS_COLOR, "In" },
		},{
			{ PINS_COLOR, "Out", }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	enum ColorType
	{
		COL_RGB,
		COL_LINEAR,
		COL_HSV,
	};

	void GetTypes(ColorType& from, ColorType& to) const {
		from = m_from;
		to = m_to;
	}
	void SetTypes(const ColorType& from, const ColorType& to) {
		m_from = from;
		m_to = to;
	}

private:
	ColorType m_from = COL_RGB, m_to = COL_RGB;

	RTTR_ENABLE(Node)

}; // ColorspaceConversion

}
}