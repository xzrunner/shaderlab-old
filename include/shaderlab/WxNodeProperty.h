#pragma once

#include <ee0/typedef.h>

#include <blueprint/Node.h>
#include <node0/typedef.h>

#include <wx/panel.h>

class wxPropertyGrid;
class wxPropertyGridEvent;

namespace shaderlab
{

class WxNodeProperty : public wxPanel
{
public:
	WxNodeProperty(wxWindow* parent, const ee0::SubjectMgrPtr& sub_mgr);

	void LoadFromNode(const ur::Device& dev,
        const n0::SceneNodePtr& obj, const bp::NodePtr& node);

private:
	void InitLayout();

    void OnPropertyGridChanging(wxPropertyGridEvent& event);
	void OnPropertyGridChanged(wxPropertyGridEvent& event);

private:
	ee0::SubjectMgrPtr m_sub_mgr;

	wxPropertyGrid* m_pg;

    n0::SceneNodePtr m_obj = nullptr;
	bp::NodePtr      m_node = nullptr;

}; // WxNodeProperty

}