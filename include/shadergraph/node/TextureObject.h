#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace facade { class Image; }

namespace sg
{
namespace node
{

class TextureObject : public Node
{
public:
	TextureObject()
		: Node("TextureObject", false)
		, m_name("tex")
	{
		AddPins(std::make_shared<Pins>(false, 0, PINS_TEXTURE2D, "Tex", *this));

		Layout();
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

	DECLARE_NODE_CLASS(TextureObject)

}; // TextureObject

}
}