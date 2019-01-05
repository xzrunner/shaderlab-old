#pragma once

#include <node0/typedef.h>

#include <wx/window.h>
#include <wx/propgrid/editors.h>

namespace sg
{

namespace node { class Custom; }

class WxCustomNodePropEditor : public wxPGTextCtrlEditor
{
    wxDECLARE_DYNAMIC_CLASS(WxCustomNodePropEditor);

public:
    WxCustomNodePropEditor() {}
    WxCustomNodePropEditor(const n0::SceneNodePtr& obj,
        const std::shared_ptr<node::Custom>& node);
    virtual ~WxCustomNodePropEditor() {}

    virtual wxString GetName() const { return "CustomPropEditor"; }
    virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid,
                                           wxPGProperty* property,
                                           const wxPoint& pos,
                                           const wxSize& sz ) const;
    virtual bool OnEvent( wxPropertyGrid* propGrid,
                          wxPGProperty* property,
                          wxWindow* ctrl,
                          wxEvent& event ) const;

private:
    n0::SceneNodePtr m_obj = nullptr;

    std::shared_ptr<node::Custom> m_node = nullptr;

}; // WxCustomNodePropEditor

}