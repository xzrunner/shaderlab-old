#pragma once

#include "shadergraph/Node.h"

#include <SM_Matrix2D.h>

namespace facade { class Image; }

namespace shadergraph
{

class TextureObject : public Node
{
public:
	TextureObject();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<TextureObject>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual std::shared_ptr<bp::node::Node> Create() const override {
		return std::make_shared<TextureObject>();
	}
	virtual void Draw(const sm::Matrix2D& mt) const override;

	void SetImage(const std::string& filepath);
	auto& GetImage() const { return m_img; }

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::node::Pins> m_output;

	std::shared_ptr<facade::Image> m_img = nullptr;

}; // TextureObject

}