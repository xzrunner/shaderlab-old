#include "shadergraph/WxCustomNodePropEditor.h"
#include "shadergraph/node/Custom.h"

#include <node0/SceneNode.h>
#include <node2/CompBoundingBox.h>

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

namespace sg
{

wxIMPLEMENT_DYNAMIC_CLASS(WxCustomNodePropEditor, wxPGTextCtrlEditor);

WxCustomNodePropEditor::WxCustomNodePropEditor(const n0::SceneNodePtr& obj,
                                               const std::shared_ptr<node::Custom>& node)
    : m_obj(obj)
    , m_node(node)
{
}

wxPGWindowList WxCustomNodePropEditor::
CreateControls(wxPropertyGrid* propGrid, wxPGProperty* property, const wxPoint& pos, const wxSize& sz) const
{
    wxPGMultiButton* buttons = new wxPGMultiButton( propGrid, sz );
    buttons->Add("+");
    buttons->Add("-");
    buttons->Add("R");
    wxPGWindowList wndList = wxPGTextCtrlEditor::CreateControls
                             ( propGrid, property, pos,
                               buttons->GetPrimarySize() );
    buttons->Finalize(propGrid, pos);
    wndList.SetSecondary( buttons );
    return wndList;
}
bool WxCustomNodePropEditor::
OnEvent(wxPropertyGrid* prop_grid, wxPGProperty* property, wxWindow* ctrl, wxEvent& event) const
{
    if ( event.GetEventType() == wxEVT_BUTTON )
    {
        wxPGMultiButton* buttons = (wxPGMultiButton*) prop_grid->GetEditorControlSecondary();
        // btn +
        if (event.GetId() == buttons->GetButtonId(0))
        {
            auto params = m_node->GetParams();

            node::Custom::Variant var;
            var.name = "param" + std::to_string(params.size());
            var.type = PINS_BOOLEAN;
            var.val.b = false;

            params.push_back(var);
            m_node->SetParams(params);
        }
        // btn -
        if (event.GetId() == buttons->GetButtonId(1))
        {
            auto params = m_node->GetParams();
            params.pop_back();
            m_node->SetParams(params);
        }
        // btn R
        if (event.GetId() == buttons->GetButtonId(2))
        {
            auto returns = m_node->GetReturns();
            if (returns.empty()) {
                node::Custom::Variant var;
                var.name = "ret";
                var.type = PINS_BOOLEAN;
                var.val.b = false;
                returns.push_back(var);
            } else {
                returns.clear();
            }
            m_node->SetReturns(returns);
        }

        auto& st = m_node->GetStyle();
        m_obj->GetUniqueComp<n2::CompBoundingBox>().SetSize(
            *m_obj, sm::rect(st.width, st.height)
        );
    }
    return wxPGTextCtrlEditor::OnEvent(prop_grid, property, ctrl, event);
}

}