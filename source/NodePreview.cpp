#include "shadergraph/NodePreview.h"
#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/Node.h"
#include "shadergraph/node/UV.h"

#include <painting2/RenderSystem.h>
#include <blueprint/Pins.h>
#include <blueprint/NodeHelper.h>

#include <queue>

namespace sg
{

NodePreview::NodePreview(const Node& node, bool debug_print)
	: m_node(node)
	, m_debug_print(debug_print)
{
}

void NodePreview::Draw(const sm::Matrix2D& mt) const
{
	if (!m_shader) {
		return;
	}

	auto model_mat = CalcNodePreviewMat(m_node, mt);
	if (m_draw_tex) {
		pt2::RenderSystem::DrawTexture(m_shader, model_mat);
	} else {
		pt2::RenderSystem::DrawColor(m_shader, model_mat);
	}
}

bool NodePreview::Update(const bp::UpdateParams& params)
{
	m_draw_tex = bp::NodeHelper::HasInputNode<node::UV>(m_node);
	if (m_draw_tex) {
		ShaderWeaver sw(ShaderWeaver::VERT_SPRITE, m_node, m_debug_print);
		m_shader = sw.CreateShader(*params.wc2);
	} else {
		ShaderWeaver sw(ShaderWeaver::VERT_SHAPE, m_node, m_debug_print);
		m_shader = sw.CreateShader(*params.wc2);
	}
	return true;
}

sm::mat4 NodePreview::CalcNodePreviewMat(const Node& node, const sm::Matrix2D& mt)
{
	auto& style = node.GetStyle();

	const float LEN = style.width;
	sm::rect r;
	r.xmin = -style.width * 0.5f; r.xmax = r.xmin + LEN;
	r.ymax = -style.height * 0.5f; r.ymin = r.ymax - LEN;

	sm::mat4 model_mat;
	model_mat.x[0]  = mt.x[0] * r.Width();
	model_mat.x[1]  = mt.x[1];
	model_mat.x[4]  = mt.x[2];
	model_mat.x[5]  = mt.x[3] * r.Height();
	model_mat.x[12] = mt.x[4] + r.Center().x;
	model_mat.x[13] = mt.x[5] + r.Center().y;

	return model_mat;
}

}