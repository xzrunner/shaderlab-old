#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/PinType.h"

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
			{ PIN_TEXTURE2D, "Tex" }
		});
	}

	virtual void Draw(const ur2::Device& dev, ur2::Context& ctx,
        const n2::RenderParams& rp) const override;

	void  SetName(const std::string& name);
	auto& GetName() const { return m_name; }

	void SetImagePath(std::string filepath);
	std::string GetImagePath() const;

	auto& GetImage() const { return m_img; }

private:
	std::string m_name;

	std::shared_ptr<facade::Image> m_img = nullptr;

	RTTR_ENABLE(Node)

}; // Tex2DAsset

}
}