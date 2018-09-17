#pragma once

#include <blueprint/Node.h>

namespace pt2 { class Shader; }

namespace sg
{
namespace node
{

class Lerp : public bp::Node
{
public:
	Lerp();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Lerp>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Lerp>();
	}
	virtual void Draw(const sm::Matrix2D& mt) const override;
	virtual bool Update(const bp::UpdateParams& params) override;

	static const std::string TYPE_NAME;

public:
	enum InputId
	{
		ID_A = 0,
		ID_B,
		ID_T
	};

private:
	std::shared_ptr<bp::Pins> m_a;
	std::shared_ptr<bp::Pins> m_b;
	std::shared_ptr<bp::Pins> m_t;

	std::shared_ptr<bp::Pins> m_output;

	std::shared_ptr<pt2::Shader> m_shader;
	bool m_draw_tex = false;

}; // Lerp

}
}