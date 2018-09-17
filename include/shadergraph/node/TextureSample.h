#pragma once

#include <blueprint/Node.h>

namespace pt2 { class Shader; }

namespace sg
{
namespace node
{

class TextureSample : public bp::Node
{
public:
	TextureSample();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<TextureSample>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<TextureSample>();
	}
	virtual void Draw(const sm::Matrix2D& mt) const override;
	virtual bool Update(const bp::UpdateParams& params) override;

	static const std::string TYPE_NAME;

public:
	enum InputId
	{
		ID_TEX = 0,
		ID_UV,
	};

private:
	// input
	std::shared_ptr<bp::Pins> m_tex;
	std::shared_ptr<bp::Pins> m_uv;

	// output
	std::shared_ptr<bp::Pins> m_rgba;
	std::shared_ptr<bp::Pins> m_r;
	std::shared_ptr<bp::Pins> m_g;
	std::shared_ptr<bp::Pins> m_b;
	std::shared_ptr<bp::Pins> m_a;

	std::shared_ptr<pt2::Shader> m_shader;

}; // TextureSample

}
}