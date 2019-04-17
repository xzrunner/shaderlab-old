#include "shadergraph/NodePreview.h"
#include "shadergraph/ShaderWeaver.h"
#include "shadergraph/Node.h"
#include "shadergraph/RegistNodes.h"

#include <painting2/RenderSystem.h>
#include <painting2/Shader.h>
#include <painting2/RenderTarget.h>
#include <painting2/RenderTargetCtx.h>
#include <painting2/Blackboard.h>
#include <painting2/RenderContext.h>
#include <blueprint/Pin.h>
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

    m_shader->Use();
	auto model_mat = sm::mat4(bp::NodeHelper::CalcPreviewMat(m_node, mt));
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
    auto& rc = ur::Blackboard::Instance()->GetRenderContext();
    int old_vl_id = rc.GetBindedVertexLayoutID();

    bool draw_tex = bp::NodeHelper::HasInputNode<node::UV>(m_node);
    std::shared_ptr<pt2::Shader> shader = nullptr;
	if (draw_tex) {
		ShaderWeaver sw(ShaderWeaver::SHADER_SPRITE, m_node, m_debug_print);
		shader = sw.CreateShader2();
	} else {
		ShaderWeaver sw(ShaderWeaver::SHADER_SHAPE, m_node, m_debug_print);
		shader = sw.CreateShader2();
	}

    if (shader->IsValid())
    {
        m_draw_tex = draw_tex;
        m_shader = shader;

        m_shader->AddNotify(std::const_pointer_cast<pt2::WindowContext>(params.wc2));
        return true;
    }
    else
    {
        rc.BindVertexLayout(old_vl_id);
        return false;
    }
}

void NodePreview::DrawTextureWithRT(const sm::mat4& mt) const
{
    // draw texture to rt

    auto& rt_mgr = pt2::Blackboard::Instance()->GetRenderContext().GetRTMgr();

    auto rt = rt_mgr.Fetch();
    rt->Bind();

    auto& ur_rc = ur::Blackboard::Instance()->GetRenderContext();
    ur_rc.SetClearColor(0);
    ur_rc.Clear();
    {
        pt2::RenderTargetCtx ctx(ur_rc, m_shader, rt_mgr.WIDTH, rt_mgr.HEIGHT);

        auto& uniform = m_shader->GetUniformName(pt0::UniformTypes::Resolution);
        if (!uniform.empty())
        {
            const float res[2] = {
                static_cast<float>(rt_mgr.WIDTH),
                static_cast<float>(rt_mgr.HEIGHT)
            };
            m_shader->SetVec2(uniform, res);
        }

        sm::mat4 mat;
        mat.Scale(
            static_cast<float>(rt_mgr.WIDTH),
            static_cast<float>(rt_mgr.HEIGHT),
            1.0f
        );
        pt2::RenderSystem::DrawTexture(m_shader, mat);
    }
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