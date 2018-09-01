#pragma once

#include "ematerial/Node.h"

#include <SM_Matrix2D.h>

namespace facade { class Image; }

namespace ematerial
{

class TextureObject : public Node
{
public:
	TextureObject();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<TextureObject>();
	}
	virtual std::string TypeName() const override {
		return "mat_tex_obj";
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<TextureObject>();
	}
	virtual void Draw(const sm::Matrix2D& mt) const override;

	void SetImage(const std::string& filepath);
	auto& GetImage() const { return m_img; }

private:
	std::shared_ptr<bp::node::Pins> m_output;

	std::shared_ptr<facade::Image> m_img = nullptr;

}; // TextureObject

}