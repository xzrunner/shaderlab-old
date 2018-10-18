#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"
#include "shadergraph/ReflectPropTypes.h"

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