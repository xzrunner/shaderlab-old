#include "shadergraph/NodePreview.h"
#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/Node.h"
#include "shadergraph/RegistNodes.h"

#include <painting2/RenderSystem.h>
#include <painting2/Shader.h>
#include <painting2/RenderTarget.h>
#include <painting2/Blackboard.h>
#include <painting2/RenderContext.h>
#include <blueprint/Pins.h>
#include <blueprint/NodeHelper.h>
#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>

#include <queue>

namespace sg
{

NodePreview::NodePreview(const Node& node, bool debug_print, bool use_rt)
	: m_node(node)
	, m_debug_print(debug_print)
    , m_use_rt(use_rt)
{
}

void NodePreview::Draw(const sm::Matrix2D& mt) const
{
	if (!m_shader) {
		return;
	}

	auto model_mat = MatTrans(CalcNodePreviewMat(m_node, mt));
    if (m_draw_tex)
    {
        if (m_use_rt) {
            DrawTextureWithRT(model_mat);
        } else {
            pt2::RenderSystem::DrawTexture(m_shader, model_mat);
        }
    }
    else
    {
		pt2::RenderSystem::DrawColor(m_shader, model_mat);
	}
}

bool NodePreview::Update(const bp::UpdateParams& params)
{
	m_draw_tex = bp::NodeHelper::HasInputNode<node::UV>(m_node);
	if (m_draw_tex) {
		ShaderWeaver sw(ShaderWeaver::SHADER_SPRITE, m_node, m_debug_print);
		m_shader = sw.CreateShader(*params.wc2);
	} else {
		ShaderWeaver sw(ShaderWeaver::SHADER_SHAPE, m_node, m_debug_print);
		m_shader = sw.CreateShader(*params.wc2);
	}
    m_shader->Use();
	return true;
}

sm::Matrix2D NodePreview::CalcNodePreviewMat(const Node& node, const sm::Matrix2D& mt)
{
	auto& style = node.GetStyle();
	const float LEN = style.width;
	sm::rect r;
	r.xmin = -style.width * 0.5f;  r.xmax = r.xmin + LEN;
	r.ymax = -style.height * 0.5f; r.ymin = r.ymax - LEN;

	sm::Matrix2D ret = mt;
	ret.x[0] *= r.Width();
	ret.x[3] *= r.Height();
	ret.x[4] += r.Center().x;
	ret.x[5] += r.Center().y;
	return ret;
}

sm::mat4 NodePreview::MatTrans(const sm::Matrix2D& mt)
{
	sm::mat4 ret;
	ret.x[0]  = mt.x[0];
	ret.x[1]  = mt.x[1];
	ret.x[4]  = mt.x[2];
	ret.x[5]  = mt.x[3];
	ret.x[12] = mt.x[4];
	ret.x[13] = mt.x[5];
	return ret;
}

void NodePreview::DrawTextureWithRT(const sm::mat4& mt) const
{
    // draw texture to rt

    auto& rc = pt2::Blackboard::Instance()->GetRenderContext();
    auto& rt_mgr = rc.GetRTMgr();

    auto rt = rt_mgr.Fetch();
    rt->Bind();

    auto& ur_rc = ur::Blackboard::Instance()->GetRenderContext();
    ur_rc.SetClearColor(0);
    ur_rc.Clear();

    m_shader->UpdateViewMat(sm::vec2(), 1);

    m_shader->SetResolution(
        static_cast<float>(rt_mgr.WIDTH),
        static_cast<float>(rt_mgr.HEIGHT)
    );

    sm::mat4 mat;
    mat.Scale(
        static_cast<float>(rt_mgr.WIDTH),
        static_cast<float>(rt_mgr.HEIGHT),
        1.0f
    );
    pt2::RenderSystem::DrawTexture(m_shader, mat);

    rt->Unbind();

    // draw rt to screen

    const auto scale = mt.GetScale();
    const float hw = scale.x * 0.5f;
    const float hh = scale.y * 0.5f;
    const auto pos = mt.GetTranslate();
    const float vertices[] = {
        pos.x - hw, pos.y - hh,
        pos.x + hw, pos.y - hh,
        pos.x + hw, pos.y + hh,
        pos.x - hw, pos.y + hh,
    };
    const float texcoords[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };
    pt2::RenderSystem::DrawTexQuad(vertices, texcoords, rt->GetTexID(), 0xffffffff);

    rt_mgr.Return(rt);
}

}