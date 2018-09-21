#include "shadergraph/WxNodeProperty.h"

// artistic
#include "shadergraph/node/ChannelMask.h"
// input
#include "shadergraph/node/Vector1.h"
#include "shadergraph/node/Vector2.h"
#include "shadergraph/node/Vector3.h"
#include "shadergraph/node/Vector4.h"
#include "shadergraph/node/Tex2DAsset.h"
// math
#include "shadergraph/node/Exponential.h"
#include "shadergraph/node/Log.h"
// uv
#include "shadergraph/node/Rotate.h"

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
	// artistic
	if (type_id == bp::GetNodeTypeID<node::ChannelMask>())
	{
		const wxChar* CHANNEL_TYPES[] = { wxT("R"), wxT("G"), wxT("B"), wxT("A"), NULL };
		const long    CHANNEL_VALUES[] = {
			sg::node::ChannelMask::CHANNEL_R,
			sg::node::ChannelMask::CHANNEL_G,
			sg::node::ChannelMask::CHANNEL_B,
			sg::node::ChannelMask::CHANNEL_A
		};

		auto& cm = dynamic_cast<const node::ChannelMask&>(*node);
		m_pg->Append(new wxFlagsProperty("Channels", wxPG_LABEL, CHANNEL_TYPES, CHANNEL_VALUES, cm.GetChannels()));
	}
	// input
	else if (type_id == bp::GetNodeTypeID<node::Vector1>())
	{
		auto& c1 = dynamic_cast<const node::Vector1&>(*node);
		m_pg->Append(new wxFloatProperty("Value", wxPG_LABEL, c1.GetValue()));
	}
	else if (type_id == bp::GetNodeTypeID<node::Vector2>())
	{
		auto& c2 = dynamic_cast<const node::Vector2&>(*node);
		auto& val = c2.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
	}
	else if (type_id == bp::GetNodeTypeID<node::Vector3>())
	{
		auto& c3 = dynamic_cast<const node::Vector3&>(*node);
		auto& val = c3.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
		m_pg->Append(new wxFloatProperty("B", wxPG_LABEL, val.z));
	}
	else if (type_id == bp::GetNodeTypeID<node::Vector4>())
	{
		auto& c4 = dynamic_cast<const node::Vector4&>(*node);
		auto& val = c4.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
		m_pg->Append(new wxFloatProperty("B", wxPG_LABEL, val.z));
		m_pg->Append(new wxFloatProperty("A", wxPG_LABEL, val.w));
	}
	else if (type_id == bp::GetNodeTypeID<node::Tex2DAsset>())
	{
		auto& t2d = dynamic_cast<const node::Tex2DAsset&>(*node);

		m_pg->Append(new wxStringProperty("name", wxPG_LABEL, t2d.GetName()));

		std::string filepath;
		if (auto& tex = t2d.GetImage()) {
			filepath = tex->GetResPath();
		}
		auto prop = new ee0::WxOpenFileProp("Filepath", wxPG_LABEL, filepath);
		prop->SetFilter("*.png");
		prop->SetCallback([&](const std::string& filepath) {
			const_cast<node::Tex2DAsset&>(t2d).SetImage(filepath);
			m_sub_mgr->NotifyObservers(bp::MSG_BLUE_PRINT_CHANGED);
		});

		m_pg->Append(prop);
	}
	// math
	else if (type_id == bp::GetNodeTypeID<node::Exponential>())
	{
		auto& exp = dynamic_cast<const node::Exponential&>(*node);

		const wxChar* EXP_TYPES[] = { wxT("BaseE"), wxT("Base2"), NULL };
		auto type_prop = new wxEnumProperty("Base", wxPG_LABEL, EXP_TYPES);
		type_prop->SetValue(exp.GetType());
		m_pg->Append(type_prop);
	}
	else if (type_id == bp::GetNodeTypeID<node::Log>())
	{
		auto& log = dynamic_cast<const node::Log&>(*node);

		const wxChar* EXP_TYPES[] = { wxT("BaseE"), wxT("Base2"), wxT("Base10"), NULL };
		auto type_prop = new wxEnumProperty("Base", wxPG_LABEL, EXP_TYPES);
		type_prop->SetValue(log.GetType());
		m_pg->Append(type_prop);
	}
	// utility
	//else if (type_id == bp::GetNodeTypeID<node::Input>())
	//{
	//	auto& input = dynamic_cast<const node::Input&>(*node);

	//	m_pg->Append(new wxStringProperty("name", wxPG_LABEL, input.GetName()));

	//const wxChar* PIN_TYPES[] = {
	//	wxT("vec1"), wxT("vec2"), wxT("vec3"), wxT("vec4"), wxT("color"), wxT("tex2d"), wxT("bool"), NULL };

	//	auto type_prop = new wxEnumProperty("type", wxPG_LABEL, PIN_TYPES);
	//	type_prop->SetValue(PIN_TYPES[input.GetType() - PINS_VECTOR1]);
	//	m_pg->Append(type_prop);
	//}
	// uv
	else if (type_id == bp::GetNodeTypeID<node::Rotate>())
	{
		auto& rot = dynamic_cast<const node::Rotate&>(*node);

		const wxChar* ROTATE_TYPES[] = { wxT("Rad"), wxT("Deg"), NULL };
		auto type_prop = new wxEnumProperty("Unit", wxPG_LABEL, ROTATE_TYPES);
		type_prop->SetValue(rot.IsRadians() ? 0 : 1);
		m_pg->Append(type_prop);
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
	// artistic
	if (type_id == bp::GetNodeTypeID<node::ChannelMask>())
	{
		if (key == "Channels") {
			auto& cm = std::dynamic_pointer_cast<node::ChannelMask>(m_node);
			cm->SetChannels(wxANY_AS(val, int));
		}
	}
	// math
	else if (type_id == bp::GetNodeTypeID<node::Exponential>())
	{
		if (key == "Base") {
			auto& exp = std::dynamic_pointer_cast<node::Exponential>(m_node);
			exp->SetType(node::Exponential::BaseType(wxANY_AS(val, int)));
		}
	}
	else if (type_id == bp::GetNodeTypeID<node::Log>())
	{
		if (key == "Base") {
			auto& log = std::dynamic_pointer_cast<node::Log>(m_node);
			log->SetType(node::Log::BaseType(wxANY_AS(val, int)));
		}
	}
	// input
	else if (type_id == bp::GetNodeTypeID<node::Vector1>())
	{
		if (key == "Value") {
			auto& c1 = std::dynamic_pointer_cast<node::Vector1>(m_node);
			c1->SetValue(wxANY_AS(val, float));
		}
	}
	else if (type_id == bp::GetNodeTypeID<node::Vector2>())
	{
		auto& c2 = std::dynamic_pointer_cast<node::Vector2>(m_node);
		auto v = c2->GetValue();
		if (key == "R") {
			v.x = wxANY_AS(val, float);
		} else if (key == "G") {
			v.y = wxANY_AS(val, float);
		}
		c2->SetValue(v);
	}
	else if (type_id == bp::GetNodeTypeID<node::Vector3>())
	{
		auto& c3 = std::dynamic_pointer_cast<node::Vector3>(m_node);
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
	else if (type_id == bp::GetNodeTypeID<node::Vector4>())
	{
		auto& c4 = std::dynamic_pointer_cast<node::Vector4>(m_node);
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
	else if (type_id == bp::GetNodeTypeID<node::Tex2DAsset>())
	{
		if (key == "name") {
			auto& t2d = std::dynamic_pointer_cast<node::Tex2DAsset>(m_node);
			t2d->SetName(wxANY_AS(val, wxString).ToStdString());
		}
	}
	// utility
	//else if (type_id == bp::GetNodeTypeID<node::Input>())
	//{
	//	auto& input = std::dynamic_pointer_cast<node::Input>(m_node);
	//	if (key == "name") {
	//		input->SetName(wxANY_AS(val, wxString).ToStdString());
	//	} else if (key == "type") {
	//		input->SetType(static_cast<PinsType>(PINS_VECTOR1 + wxANY_AS(val, int)));
	//	}
	//}
	// uv
	else if (type_id == bp::GetNodeTypeID<node::Rotate>())
	{
		if (key == "Unit") {
			auto& rot = std::dynamic_pointer_cast<node::Rotate>(m_node);
			rot->SetRadians(wxANY_AS(val, int) == 0);
		}
	}

	// todo
	m_sub_mgr->NotifyObservers(bp::MSG_BLUE_PRINT_CHANGED);
}

}