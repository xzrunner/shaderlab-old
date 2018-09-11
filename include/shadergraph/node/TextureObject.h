#pragma once

#include "shadergraph/Node.h"

#include <SM_Matrix2D.h>

namespace facade { class Image; }

namespace sg
{
namespace node
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
	virtual bp::NodePtr Create() const override {
		return std::make_shared<TextureObject>();
	}
	virtual void Draw(const sm::Matrix2D& mt) const override;

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	void SetImage(const std::string& filepath);
	auto& GetImage() const { return m_img; }

	static const std::string TYPE_NAME;

private:
	std::shared_ptr<bp::Pins> m_output;

	std::shared_ptr<facade::Image> m_img = nullptr;

}; // TextureObject

}
}