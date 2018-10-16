#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace facade { class Image; }

namespace sg
{
namespace node
{

class Tex2DAsset : public Node
{
public:
	Tex2DAsset()
		: Node("Tex2DAsset", false)
		, m_name("tex")
	{
		InitPins({
		},{
			{ PINS_TEXTURE2D, "Tex" }
		});
	}

	virtual void Draw(const sm::Matrix2D& mt) const override;

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	void  SetName(const std::string& name);
	auto& GetName() const { return m_name; }

	void  SetImage(const std::string& filepath);
	auto& GetImage() const { return m_img; }

private:
	std::string m_name;

	std::shared_ptr<facade::Image> m_img = nullptr;

	RTTR_ENABLE(Node)

}; // Tex2DAsset

}
}