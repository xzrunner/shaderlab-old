#include "shadergraph/WxNodeProperty.h"
#include "shadergraph/node/Constant1.h"
#include "shadergraph/node/Constant2.h"
#include "shadergraph/node/Constant3.h"
#include "shadergraph/node/Constant4.h"
#include "shadergraph/node/TextureObject.h"

#include <ee0/SubjectMgr.h>
#include <ee0/WxOpenFileProp.h>
#include <blueprint/MessageID.h>
#include <facade/Image.h>

#include <wx/sizer.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

namespace sg
{

WxNodeProperty::WxNodeProperty(wxWindow* parent, const ee0::SubjectMgrPtr& sub_mgr)
	: wxPanel(parent)
	, m_sub_mgr(sub_mgr)
{
	InitLayout();
}

void WxNodeProperty::LoadFromNode(const bp::NodePtr& node)
{
	m_node = node;

	m_pg->Clear();

	auto type_id = node->TypeID();
	if (type_id == bp::GetNodeTypeID<node::Constant1>())
	{
		auto& c1 = dynamic_cast<const node::Constant1&>(*node);
		m_pg->Append(new wxFloatProperty("Value", wxPG_LABEL, c1.GetValue()));
	}
	else if (type_id == bp::GetNodeTypeID<node::Constant2>())
	{
		auto& c2 = dynamic_cast<const node::Constant2&>(*node);
		auto& val = c2.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
	}
	else if (type_id == bp::GetNodeTypeID<node::Constant3>())
	{
		auto& c3 = dynamic_cast<const node::Constant3&>(*node);
		auto& val = c3.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
		m_pg->Append(new wxFloatProperty("B", wxPG_LABEL, val.z));
	}
	else if (type_id == bp::GetNodeTypeID<node::Constant4>())
	{
		auto& c4 = dynamic_cast<const node::Constant4&>(*node);
		auto& val = c4.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
		m_pg->Append(new wxFloatProperty("B", wxPG_LABEL, val.z));
		m_pg->Append(new wxFloatProperty("A", wxPG_LABEL, val.w));
	}
	else if (type_id == bp::GetNodeTypeID<node::TextureObject>())
	{
		auto& to = dynamic_cast<const node::TextureObject&>(*node);
		std::string filepath;
		if (auto& tex = to.GetImage()) {
			filepath = tex->GetResPath();
		}
		auto prop = new ee0::WxOpenFileProp("Filepath", wxPG_LABEL, filepath);
		prop->SetFilter("*.png");
		prop->SetCallback([&](const std::string& filepath) {
			const_cast<node::TextureObject&>(to).SetImage(filepath);
			m_sub_mgr->NotifyObservers(bp::MSG_BLUE_PRINT_CHANGED);
		});
		m_pg->Append(prop);
	}
}

void WxNodeProperty::InitLayout()
{
	auto sizer = new wxBoxSizer(wxVERTICAL);

	m_pg = new wxPropertyGrid(this, -1, wxDefaultPosition, wxSize(300, 600),
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
	);
	Connect(m_pg->GetId(), wxEVT_PG_CHANGED, wxPropertyGridEventHandler(
		WxNodeProperty::OnPropertyGridChange));
	sizer->Add(m_pg, 1, wxEXPAND);

	SetSizer(sizer);
}

void WxNodeProperty::OnPropertyGridChange(wxPropertyGridEvent& event)
{
	if (!m_node) {
		return;
	}

	wxPGProperty* property = event.GetProperty();
	auto key = property->GetName();
	wxAny val = property->GetValue();

	auto type_id = m_node->TypeID();
	if (type_id == bp::GetNodeTypeID<node::Constant1>())
	{
		auto& c1 = std::dynamic_pointer_cast<node::Constant1>(m_node);
		if (key == "Value") {
			c1->SetValue(wxANY_AS(val, float));
		}
	}
	else if (type_id == bp::GetNodeTypeID<node::Constant2>())
	{
		auto& c2 = std::dynamic_pointer_cast<node::Constant2>(m_node);
		auto v = c2->GetValue();
		if (key == "R") {
			v.x = wxANY_AS(val, float);
		} else if (key == "G") {
			v.y = wxANY_AS(val, float);
		}
		c2->SetValue(v);
	}
	else if (type_id == bp::GetNodeTypeID<node::Constant3>())
	{
		auto& c3 = std::dynamic_pointer_cast<node::Constant3>(m_node);
		auto v = c3->GetValue();
		if (key == "R") {
			v.x = wxANY_AS(val, float);
		} else if (key == "G") {
			v.y = wxANY_AS(val, float);
		} else if (key == "B") {
			v.z = wxANY_AS(val, float);
		}
		c3->SetValue(v);
	}
	else if (type_id == bp::GetNodeTypeID<node::Constant4>())
	{
		auto& c4 = std::dynamic_pointer_cast<node::Constant4>(m_node);
		auto v = c4->GetValue();
		if (key == "R") {
			v.x = wxANY_AS(val, float);
		} else if (key == "G") {
			v.y = wxANY_AS(val, float);
		} else if (key == "B") {
			v.z = wxANY_AS(val, float);
		} else if (key == "A") {
			v.w = wxANY_AS(val, float);
		}
		c4->SetValue(v);
	}

	// todo
	m_sub_mgr->NotifyObservers(bp::MSG_BLUE_PRINT_CHANGED);
}

}