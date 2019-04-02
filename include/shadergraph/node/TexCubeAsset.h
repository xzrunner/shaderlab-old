#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/PinsType.h"

namespace facade { class ImageCube; }

namespace sg
{
namespace node
{

class TexCubeAsset : public Node
{
public:
	TexCubeAsset()
		: Node("TexCubeAsset", false)
		, m_name("tex")
	{
		InitPins({
		},{
			{ PINS_CUBE_MAP, "Tex" }
		});
	}

	virtual void Draw(const n2::RenderParams& rp) const override;

	void  SetName(const std::string& name);
	auto& GetName() const { return m_name; }

	void SetImagePath(std::string filepath);
	std::string GetImagePath() const;

	auto& GetImage() const { return m_img; }

private:
	std::string m_name;

	std::shared_ptr<facade::ImageCube> m_img = nullptr;

	RTTR_ENABLE(Node)

}; // TexCubeAsset

}
}