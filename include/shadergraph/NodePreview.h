#pragma once

#include <SM_Matrix2D.h>
#include <SM_Matrix.h>

#include <memory>

namespace bp { struct UpdateParams; }
namespace pt2 { class Shader; }

namespace sg
{

class Node;

class NodePreview
{
public:
	NodePreview(const Node& node);

	void Draw(const sm::Matrix2D& mt) const;
	bool Update(const bp::UpdateParams& params);

	static sm::mat4 CalcNodePreviewMat(const Node& node,
		const sm::Matrix2D& mt);

private:
	bool HasInputTexture() const;

private:
	const Node& m_node;

	std::shared_ptr<pt2::Shader> m_shader = nullptr;
	bool m_draw_tex = false;

}; // NodePreview

}