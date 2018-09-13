#pragma once

#include <blueprint/Node.h>

#include <SM_Matrix2D.h>

namespace facade { class Image; }
namespace ur { class Shader; }

namespace sg
{
namespace node
{

class TextureObject : public bp::Node
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
	virtual void Update() override;

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	void  SetName(const std::string& name);
	auto& GetName() const { return m_name; }

	void  SetImage(const std::string& filepath);
	auto& GetImage() const { return m_img; }

	static const std::string TYPE_NAME;

private:
	void DrawImage(const sm::Matrix2D& mt) const;

private:
	std::string m_name;

	std::shared_ptr<bp::Pins> m_output;

	std::shared_ptr<facade::Image> m_img = nullptr;

	std::shared_ptr<ur::Shader> m_shader;

}; // TextureObject

}
}