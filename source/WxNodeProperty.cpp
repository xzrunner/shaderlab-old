#include "shadergraph/WxNodeProperty.h"
#include "shadergraph/ReflectPropTypes.h"

#include <ee0/SubjectMgr.h>
#include <ee0/ReflectPropTypes.h>
#include <ee0/MessageID.h>
#include <ee0/WxPropHelper.h>
#include <blueprint/MessageID.h>

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

	for (auto& prop : type.get_properties())
	{
		auto ui_info_obj = prop.get_metadata(ee0::UIMetaInfoTag());
		if (!ui_info_obj.is_valid()) {
			continue;
		}

		auto ui_info = ui_info_obj.get_value<ee0::UIMetaInfo>();
		auto type = prop.get_type();
		if (type == rttr::type::get<PropAngleType>())
		{
			const wxChar* ANDLE_TYPES[] = { wxT("Deg"), wxT("Rad"), NULL };
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, ANDLE_TYPES);
			auto angle_type = prop.get_value(node).get_value<PropAngleType>();
			type_prop->SetValue(static_cast<int>(angle_type));
			m_pg->Append(type_prop);
		}
		else if (type == rttr::type::get<PropMultiChannels>())
		{
			const wxChar* CHANNEL_TYPES[] = { wxT("R"), wxT("G"), wxT("B"), wxT("A"), NULL };
			const long    CHANNEL_VALUES[] = {
				sg::PropMultiChannels::CHANNEL_R,
				sg::PropMultiChannels::CHANNEL_G,
				sg::PropMultiChannels::CHANNEL_B,
				sg::PropMultiChannels::CHANNEL_A
			};
			auto channels = prop.get_value(node).get_value<PropMultiChannels>().channels;
			m_pg->Append(new wxFlagsProperty(ui_info.desc, wxPG_LABEL, CHANNEL_TYPES, CHANNEL_VALUES, channels));
		}
		else if (type == rttr::type::get<PropBlendMode>())
		{
			const wxChar* MODES[] = { wxT("Burn"), wxT("Darken"), wxT("Difference"), wxT("Dodge"), wxT("Divide"), wxT("Exclusion"),
				wxT("HardLight"), wxT("HardMix"), wxT("Lighten"), wxT("LinearBurn"), wxT("LinearDodge"), wxT("LinearLight"),
				wxT("LinearLightAddSub"), wxT("Multiply"), wxT("Negation"), wxT("Overlay"), wxT("PinLight"), wxT("Screen"),
				wxT("SoftLight"), wxT("Subtract"), wxT("VividLight"), NULL };
			auto mode_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, MODES);
			auto mode = prop.get_value(node).get_value<PropBlendMode>().mode;
			mode_prop->SetValue(static_cast<int>(mode));
			m_pg->Append(mode_prop);
		}
		else if (type == rttr::type::get<PropColorTrans>())
		{
			const wxChar* COL_TYPES[] = { wxT("RGB"), wxT("Linear"), wxT("HSV"), NULL };

			auto& type = prop.get_value(node).get_value<PropColorTrans>();

			auto from_prop = new wxEnumProperty("From", wxPG_LABEL, COL_TYPES);
			from_prop->SetValue(static_cast<int>(type.from));
			m_pg->Append(from_prop);

			auto to_prop = new wxEnumProperty("To", wxPG_LABEL, COL_TYPES);
			to_prop->SetValue(static_cast<int>(type.to));
			m_pg->Append(to_prop);
		}
		else if (type == rttr::type::get<PropChannelArray>())
		{
			const wxChar* CHANNEL_TYPES[] = { wxT("R"), wxT("G"), wxT("B"), wxT("A"), NULL };

			auto& channels = prop.get_value(node).get_value<PropChannelArray>().channels;

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
		// math
		else if (type == rttr::type::get<PropMathBaseType>())
		{
			const wxChar* EXP_TYPES[] = { wxT("BaseE"), wxT("Base2"), wxT("Base10"), NULL };
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, EXP_TYPES);
			auto& type = prop.get_value(node).get_value<PropMathBaseType>();
			type_prop->SetValue(static_cast<int>(type));
			m_pg->Append(type_prop);
		}
		else if (type == rttr::type::get<MatrixType>())
		{
			const wxChar* TYPES[] = { wxT("Row"), wxT("Column"), NULL };
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, TYPES);
			auto& type = prop.get_value(node).get_value<MatrixType>();
			type_prop->SetValue(static_cast<int>(type));
			m_pg->Append(type_prop);
		}
		// utility
		else if (type == rttr::type::get<CmpType>())
		{
			const wxChar* CMP_TYPES[] = {
				wxT("Equal"), wxT("Not Equal"), wxT("Less"), wxT("Less or Equal"),
				wxT("Greater"), wxT("Greater or Equal"), NULL
			};
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, CMP_TYPES);
			auto& type = prop.get_value(node).get_value<CmpType>();
			type_prop->SetValue(static_cast<int>(type));
			m_pg->Append(type_prop);
		}
		else
		{
			ee0::WxPropHelper::CreateProp(m_pg, ui_info, node, prop);
		}
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

	auto node_type = m_node->get_type();
	for (auto& prop : node_type.get_properties())
	{
		auto ui_info_obj = prop.get_metadata(ee0::UIMetaInfoTag());
		if (!ui_info_obj.is_valid()) {
			continue;
		}
		auto ui_info = ui_info_obj.get_value<ee0::UIMetaInfo>();
		auto type = prop.get_type();
		if (type == rttr::type::get<PropAngleType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<PropAngleType>(wxANY_AS(val, int)));
		}
		else if (type == rttr::type::get<PropMultiChannels>() && key == ui_info.desc)
		{
			prop.set_value(m_node, PropMultiChannels(wxANY_AS(val, int)));
		}
		else if (type == rttr::type::get<PropBlendMode>() && key == ui_info.desc)
		{
			prop.set_value(m_node, PropBlendMode(wxANY_AS(val, int)));
		}
		else if (type == rttr::type::get<PropColorTrans>() && (key == "From" || key == "To"))
		{
			auto type = prop.get_value(m_node).get_value<PropColorTrans>();
			if (key == "From") {
				type.from = static_cast<ColorType>(wxANY_AS(val, int));
			} else if (key == "To") {
				type.to = static_cast<ColorType>(wxANY_AS(val, int));
			}
			prop.set_value(m_node, type);
		}
		else if (type == rttr::type::get<PropChannelArray>() && (key == "R" || key == "G" || key == "B" || key == "A"))
		{
			auto channels = prop.get_value(m_node).get_value<PropChannelArray>();
			if (key == "R") {
				channels.channels[0] = static_cast<ChannelType>(wxANY_AS(val, int));
			} else if (key == "G") {
				channels.channels[1] = static_cast<ChannelType>(wxANY_AS(val, int));
			} else if (key == "B") {
				channels.channels[2] = static_cast<ChannelType>(wxANY_AS(val, int));
			} else if (key == "A") {
				channels.channels[3] = static_cast<ChannelType>(wxANY_AS(val, int));
			}
			prop.set_value(m_node, channels);
		}
		// math
		else if (type == rttr::type::get<PropMathBaseType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<PropMathBaseType>(wxANY_AS(val, int)));
		}
		else if (type == rttr::type::get<MatrixType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<MatrixType>(wxANY_AS(val, int)));
		}
		else if (type == rttr::type::get<CmpType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<CmpType>(wxANY_AS(val, int)));
		}
		else
		{
			ee0::WxPropHelper::UpdateProp(key, val, ui_info, m_node, prop);
		}
	}

	m_node->Refresh();

	m_sub_mgr->NotifyObservers(ee0::MSG_SET_CANVAS_DIRTY);
	m_sub_mgr->NotifyObservers(bp::MSG_BLUE_PRINT_CHANGED);
}

}