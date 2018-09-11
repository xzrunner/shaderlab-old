#pragma once

#include <ee0/typedef.h>

#include <blueprint/Node.h>

#include <wx/panel.h>

class wxPropertyGrid;
class wxPropertyGridEvent;

namespace sg
{

class WxNodeProperty : public wxPanel
{
public:
	WxNodeProperty(wxWindow* parent, const ee0::SubjectMgrPtr& sub_mgr);

	void LoadFromNode(const bp::NodePtr& node);

private:
	void InitLayout();

	void OnPropertyGridChange(wxPropertyGridEvent& event);

private:
	ee0::SubjectMgrPtr m_sub_mgr;

	wxPropertyGrid* m_pg;

	bp::NodePtr m_node = nullptr;

}; // WxNodeProperty

}