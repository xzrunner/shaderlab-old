#include "shadergraph/WxNodeProperty.h"

// artistic
#include "shadergraph/node/Hue.h"
#include "shadergraph/node/InvertColors.h"
#include "shadergraph/node/Blend.h"
#include "shadergraph/node/ChannelMask.h"
#include "shadergraph/node/ColorspaceConversion.h"
// channel
#include "shadergraph/node/Flip.h"
#include "shadergraph/node/Swizzle.h"
// input
#include "shadergraph/node/Boolean.h"
#include "shadergraph/node/Vector1.h"
#include "shadergraph/node/Vector2.h"
#include "shadergraph/node/Vector3.h"
#include "shadergraph/node/Vector4.h"
#include "shadergraph/node/Tex2DAsset.h"
// math
#include "shadergraph/node/Exponential.h"
#include "shadergraph/node/Log.h"
#include "shadergraph/node/MatrixConstruction.h"
#include "shadergraph/node/MatrixSplit.h"
// utility
#include "shadergraph/node/Comparison.h"
// uv
#include "shadergraph/node/Flipbook.h"
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

	auto type = node->get_type();
	// artistic
	if (type == rttr::type::get<node::Hue>())
	{
		auto& hue = dynamic_cast<const node::Hue&>(*node);

		const wxChar* ROTATE_TYPES[] = { wxT("Rad"), wxT("Deg"), NULL };
		auto type_prop = new wxEnumProperty("Unit", wxPG_LABEL, ROTATE_TYPES);
		type_prop->SetValue(hue.IsRadians() ? 0 : 1);
		m_pg->Append(type_prop);
	}
	else if (type == rttr::type::get<node::InvertColors>())
	{
		const wxChar* CHANNEL_TYPES[] = { wxT("R"), wxT("G"), wxT("B"), wxT("A"), NULL };
		const long    CHANNEL_VALUES[] = {
			sg::node::InvertColors::CHANNEL_R,
			sg::node::InvertColors::CHANNEL_G,
			sg::node::InvertColors::CHANNEL_B,
			sg::node::InvertColors::CHANNEL_A
		};

		auto& flip = dynamic_cast<const node::InvertColors&>(*node);
		m_pg->Append(new wxFlagsProperty("Channels", wxPG_LABEL, CHANNEL_TYPES, CHANNEL_VALUES, flip.GetChannels()));
	}
	else if (type == rttr::type::get<node::Blend>())
	{
		auto& blend = dynamic_cast<const node::Blend&>(*node);

		const wxChar* MODES[] = { wxT("Burn"), wxT("Darken"), wxT("Difference"), wxT("Dodge"), wxT("Divide"), wxT("Exclusion"),
			wxT("HardLight"), wxT("HardMix"), wxT("Lighten"), wxT("LinearBurn"), wxT("LinearDodge"), wxT("LinearLight"),
			wxT("LinearLightAddSub"), wxT("Multiply"), wxT("Negation"), wxT("Overlay"), wxT("PinLight"), wxT("Screen"),
			wxT("SoftLight"), wxT("Subtract"), wxT("VividLight"), NULL };
		auto mode_prop = new wxEnumProperty("Mode", wxPG_LABEL, MODES);
		mode_prop->SetValue(blend.GetMode());
		m_pg->Append(mode_prop);
	}
	else if (type == rttr::type::get<node::ChannelMask>())
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
	else if (type == rttr::type::get<node::ColorspaceConversion>())
	{
		auto& conv = dynamic_cast<const node::ColorspaceConversion&>(*node);
		node::ColorspaceConversion::ColorType from, to;
		conv.GetTypes(from, to);

		const wxChar* COL_TYPES[] = { wxT("RGB"), wxT("Linear"), wxT("HSV"), NULL };

		auto from_prop = new wxEnumProperty("From", wxPG_LABEL, COL_TYPES);
		from_prop->SetValue(static_cast<int>(from));
		m_pg->Append(from_prop);

		auto to_prop = new wxEnumProperty("To", wxPG_LABEL, COL_TYPES);
		to_prop->SetValue(static_cast<int>(to));
		m_pg->Append(to_prop);
	}
	// channel
	else if (type == rttr::type::get<node::Flip>())
	{
		const wxChar* CHANNEL_TYPES[] = { wxT("R"), wxT("G"), wxT("B"), wxT("A"), NULL };
		const long    CHANNEL_VALUES[] = {
			sg::node::Flip::CHANNEL_R,
			sg::node::Flip::CHANNEL_G,
			sg::node::Flip::CHANNEL_B,
			sg::node::Flip::CHANNEL_A
		};

		auto& flip = dynamic_cast<const node::Flip&>(*node);
		m_pg->Append(new wxFlagsProperty("Channels", wxPG_LABEL, CHANNEL_TYPES, CHANNEL_VALUES, flip.GetChannels()));
	}
	else if (type == rttr::type::get<node::Swizzle>())
	{
		auto& swizzle = dynamic_cast<const node::Swizzle&>(*node);
		uint32_t channels[4];
		swizzle.GetChannels(channels);

		const wxChar* CHANNEL_TYPES[] = { wxT("R"), wxT("G"), wxT("B"), wxT("A"), NULL };

		auto r_prop = new wxEnumProperty("R", wxPG_LABEL, CHANNEL_TYPES);
		r_prop->SetValue(int(channels[0]));
		m_pg->Append(r_prop);

		auto g_prop = new wxEnumProperty("G", wxPG_LABEL, CHANNEL_TYPES);
		g_prop->SetValue(int(channels[1]));
		m_pg->Append(g_prop);

		auto b_prop = new wxEnumProperty("B", wxPG_LABEL, CHANNEL_TYPES);
		b_prop->SetValue(int(channels[2]));
		m_pg->Append(b_prop);

		auto a_prop = new wxEnumProperty("A", wxPG_LABEL, CHANNEL_TYPES);
		a_prop->SetValue(int(channels[3]));
		m_pg->Append(a_prop);
	}
	// input
	else if (type == rttr::type::get<node::Boolean>())
	{
		auto& b = dynamic_cast<const node::Boolean&>(*node);
		m_pg->Append(new wxBoolProperty("Value", wxPG_LABEL, b.GetValue()));
	}
	else if (type == rttr::type::get<node::Vector1>())
	{
		auto& c1 = dynamic_cast<const node::Vector1&>(*node);
		m_pg->Append(new wxFloatProperty("Value", wxPG_LABEL, c1.GetValue()));
	}
	else if (type == rttr::type::get<node::Vector2>())
	{
		auto& c2 = dynamic_cast<const node::Vector2&>(*node);
		auto& val = c2.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
	}
	else if (type == rttr::type::get<node::Vector3>())
	{
		auto& c3 = dynamic_cast<const node::Vector3&>(*node);
		auto& val = c3.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
		m_pg->Append(new wxFloatProperty("B", wxPG_LABEL, val.z));
	}
	else if (type == rttr::type::get<node::Vector4>())
	{
		auto& c4 = dynamic_cast<const node::Vector4&>(*node);
		auto& val = c4.GetValue();
		m_pg->Append(new wxFloatProperty("R", wxPG_LABEL, val.x));
		m_pg->Append(new wxFloatProperty("G", wxPG_LABEL, val.y));
		m_pg->Append(new wxFloatProperty("B", wxPG_LABEL, val.z));
		m_pg->Append(new wxFloatProperty("A", wxPG_LABEL, val.w));
	}
	else if (type == rttr::type::get<node::Tex2DAsset>())
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
	else if (type == rttr::type::get<node::Exponential>())
	{
		auto& exp = dynamic_cast<const node::Exponential&>(*node);

		const wxChar* EXP_TYPES[] = { wxT("BaseE"), wxT("Base2"), NULL };
		auto type_prop = new wxEnumProperty("Base", wxPG_LABEL, EXP_TYPES);
		type_prop->SetValue(exp.GetType());
		m_pg->Append(type_prop);
	}
	else if (type == rttr::type::get<node::Log>())
	{
		auto& log = dynamic_cast<const node::Log&>(*node);

		const wxChar* EXP_TYPES[] = { wxT("BaseE"), wxT("Base2"), wxT("Base10"), NULL };
		auto type_prop = new wxEnumProperty("Base", wxPG_LABEL, EXP_TYPES);
		type_prop->SetValue(log.GetType());
		m_pg->Append(type_prop);
	}
	else if (type == rttr::type::get<node::MatrixConstruction>())
	{
		auto& mc = dynamic_cast<const node::MatrixConstruction&>(*node);

		const wxChar* TYPES[] = { wxT("Row"), wxT("Column"), NULL };
		auto type_prop = new wxEnumProperty("Mat", wxPG_LABEL, TYPES);
		type_prop->SetValue(mc.IsRow() ? 0 : 1);
		m_pg->Append(type_prop);
	}
	else if (type == rttr::type::get<node::MatrixSplit>())
	{
		auto& ms = dynamic_cast<const node::MatrixSplit&>(*node);

		const wxChar* TYPES[] = { wxT("Row"), wxT("Column"), NULL };
		auto type_prop = new wxEnumProperty("Mat", wxPG_LABEL, TYPES);
		type_prop->SetValue(ms.IsRow() ? 0 : 1);
		m_pg->Append(type_prop);
	}
	// utility
	else if (type == rttr::type::get<node::Comparison>())
	{
		auto& cmp = dynamic_cast<const node::Comparison&>(*node);

		const wxChar* CMP_TYPES[] = {
			wxT("Equal"), wxT("Not Equal"), wxT("Less"), wxT("Less or Equal"),
			wxT("Greater"), wxT("Greater or Equal"), NULL
		};
		auto type_prop = new wxEnumProperty("Cmp", wxPG_LABEL, CMP_TYPES);
		type_prop->SetValue(cmp.GetCmpType());
		m_pg->Append(type_prop);
	}
	//else if (type == rttr::type::get<node::Input>())
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
	else if (type == rttr::type::get<node::Flipbook>())
	{
		auto& fb = dynamic_cast<const node::Flipbook&>(*node);
		auto& invert = fb.GetInvert();

		m_pg->Append(new wxBoolProperty("Invert X", wxPG_LABEL, invert.x));
		m_pg->SetPropertyAttribute("Invert X", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
		m_pg->Append(new wxBoolProperty("Invert Y", wxPG_LABEL, invert.y));
		m_pg->SetPropertyAttribute("Invert Y", wxPG_BOOL_USE_CHECKBOX, true, wxPG_RECURSE);
	}
	else if (type == rttr::type::get<node::Rotate>())
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

	auto type = m_node->get_type();
	// artistic
	if (type == rttr::type::get<node::Hue>())
	{
		if (key == "Unit") {
			auto& hue = std::dynamic_pointer_cast<node::Hue>(m_node);
			hue->SetRadians(wxANY_AS(val, int) == 0);
		}
	}
	else if (type == rttr::type::get<node::InvertColors>())
	{
		if (key == "Channels") {
			auto& flip = std::dynamic_pointer_cast<node::InvertColors>(m_node);
			flip->SetChannels(wxANY_AS(val, int));
		}
	}
	else if (type == rttr::type::get<node::Blend>())
	{
		if (key == "Mode") {
			auto& blend = std::dynamic_pointer_cast<node::Blend>(m_node);
			blend->SetMode(static_cast<sw::node::Blend::ModeType>(wxANY_AS(val, int)));
		}
	}
	else if (type == rttr::type::get<node::ChannelMask>())
	{
		if (key == "Channels") {
			auto& cm = std::dynamic_pointer_cast<node::ChannelMask>(m_node);
			cm->SetChannels(wxANY_AS(val, int));
		}
	}
	else if (type == rttr::type::get<node::ColorspaceConversion>())
	{
		node::ColorspaceConversion::ColorType f, t;
		auto& conv = std::dynamic_pointer_cast<node::ColorspaceConversion>(m_node);
		conv->GetTypes(f, t);
		if (key == "From") {
			conv->SetTypes(static_cast<node::ColorspaceConversion::ColorType>(wxANY_AS(val, int)), t);
		} else if (key == "To") {
			conv->SetTypes(f, static_cast<node::ColorspaceConversion::ColorType>(wxANY_AS(val, int)));
		}
	}
	// channel
	else if (type == rttr::type::get<node::Flip>())
	{
		if (key == "Channels") {
			auto& flip = std::dynamic_pointer_cast<node::Flip>(m_node);
			flip->SetChannels(wxANY_AS(val, int));
		}
	}
	else if (type == rttr::type::get<node::Swizzle>())
	{
		uint32_t channels[4];
		auto& swizzle = std::dynamic_pointer_cast<node::Swizzle>(m_node);
		swizzle->GetChannels(channels);
		if (key == "R") {
			channels[0] = wxANY_AS(val, int);
		} else if (key == "G") {
			channels[1] = wxANY_AS(val, int);
		} else if (key == "B") {
			channels[2] = wxANY_AS(val, int);
		} else if (key == "A") {
			channels[3] = wxANY_AS(val, int);
		}
		swizzle->SetChannels(channels);
	}
	// math
	else if (type == rttr::type::get<node::Exponential>())
	{
		if (key == "Base") {
			auto& exp = std::dynamic_pointer_cast<node::Exponential>(m_node);
			exp->SetType(node::Exponential::BaseType(wxANY_AS(val, int)));
		}
	}
	else if (type == rttr::type::get<node::Log>())
	{
		if (key == "Base") {
			auto& log = std::dynamic_pointer_cast<node::Log>(m_node);
			log->SetType(node::Log::BaseType(wxANY_AS(val, int)));
		}
	}
	else if (type == rttr::type::get<node::MatrixConstruction>())
	{
		if (key == "Mat") {
			auto& mc = std::dynamic_pointer_cast<node::MatrixConstruction>(m_node);
			mc->SetRow(wxANY_AS(val, int) == 0);
		}
	}
	else if (type == rttr::type::get<node::MatrixSplit>())
	{
		if (key == "Mat") {
			auto& ms = std::dynamic_pointer_cast<node::MatrixSplit>(m_node);
			ms->SetRow(wxANY_AS(val, int) == 0);
		}
	}
	// input
	else if (type == rttr::type::get<node::Boolean>())
	{
		if (key == "Value") {
			auto& b = std::dynamic_pointer_cast<node::Boolean>(m_node);
			b->SetValue(wxANY_AS(val, bool));
		}
	}
	else if (type == rttr::type::get<node::Vector1>())
	{
		if (key == "Value") {
			auto& c1 = std::dynamic_pointer_cast<node::Vector1>(m_node);
			c1->SetValue(wxANY_AS(val, float));
		}
	}
	else if (type == rttr::type::get<node::Vector2>())
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
	else if (type == rttr::type::get<node::Vector3>())
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
	else if (type == rttr::type::get<node::Vector4>())
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
	else if (type == rttr::type::get<node::Tex2DAsset>())
	{
		if (key == "name") {
			auto& t2d = std::dynamic_pointer_cast<node::Tex2DAsset>(m_node);
			t2d->SetName(wxANY_AS(val, wxString).ToStdString());
		}
	}
	// utility
	else if (type == rttr::type::get<node::Comparison>())
	{
		if (key == "Cmp") {
			auto& cmp = std::dynamic_pointer_cast<node::Comparison>(m_node);
			cmp->SetCmpType(static_cast<node::Comparison::CmpType>(wxANY_AS(val, int)));
		}
	}
	//else if (type == rttr::type::get<node::Input>())
	//{
	//	auto& input = std::dynamic_pointer_cast<node::Input>(m_node);
	//	if (key == "name") {
	//		input->SetName(wxANY_AS(val, wxString).ToStdString());
	//	} else if (key == "type") {
	//		input->SetType(static_cast<PinsType>(PINS_VECTOR1 + wxANY_AS(val, int)));
	//	}
	//}
	// uv
	else if (type == rttr::type::get<node::Flipbook>())
	{
		auto& fb = std::dynamic_pointer_cast<node::Flipbook>(m_node);
		if (key == "Invert X") {
			fb->SetInvert(sm::bvec2(wxANY_AS(val, bool), fb->GetInvert().y));
		} else if (key == "Invert Y") {
			fb->SetInvert(sm::bvec2(fb->GetInvert().x, wxANY_AS(val, bool)));
		}
	}
	else if (type == rttr::type::get<node::Rotate>())
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