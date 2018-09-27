#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Flipbook : public Node
{
public:
	Flipbook()
		: Node("Flipbook", true)
	{
		InitPins({
			{ PINS_VECTOR2, "UV" },
			{ PINS_VECTOR1, "Width" },
			{ PINS_VECTOR1, "Height" },
			{ PINS_VECTOR1, "Tile" },
		},{
			{ PINS_VECTOR2, "Out", }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	auto& GetInvert() const { return m_invert; }
	void SetInvert(const sm::bvec2& invert) { m_invert = invert; }

public:
	enum InputID
	{
		ID_UV = 0,
		ID_WIDTH,
		ID_HEIGHT,
		ID_TILE,
	};

private:
	sm::bvec2 m_invert;

	DECLARE_NODE_CLASS(Flipbook)

}; // Flipbook

}
}