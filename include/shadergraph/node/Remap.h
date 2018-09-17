#pragma once

#include <blueprint/Node.h>

namespace pt2 { class Shader; }

namespace sg
{
namespace node
{

class Remap : public bp::Node
{
public:
	Remap();

	virtual bp::NodeTypeID TypeID() const override {
		return bp::GetNodeTypeID<Remap>();
	}
	virtual const std::string& TypeName() const override {
		return TYPE_NAME;
	}
	virtual bp::NodePtr Create() const override {
		return std::make_shared<Remap>();
	}
	virtual void Draw(const sm::Matrix2D& mt) const override;
	virtual bool Update(const bp::UpdateParams& params) override;

	static const std::string TYPE_NAME;

public:
	enum InputId
	{
		ID_IN = 0,
		ID_FROM,
		ID_TO
	};

private:
	std::shared_ptr<bp::Pins> m_in;
	std::shared_ptr<bp::Pins> m_from;
	std::shared_ptr<bp::Pins> m_to;

	std::shared_ptr<bp::Pins> m_output;

	std::shared_ptr<pt2::Shader> m_shader;
	bool m_draw_tex = false;

}; // Remap

}
}