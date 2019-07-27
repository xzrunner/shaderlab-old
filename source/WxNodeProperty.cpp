#include "shadergraph/WxNodeProperty.h"
#include "shadergraph/ReflectPropTypes.h"
#include "shadergraph/RegistNodes.h"
#include "shadergraph/TypeDeduction.h"

#include <ee0/SubjectMgr.h>
#include <ee0/ReflectPropTypes.h>
#include <ee0/MessageID.h>
#include <ee0/WxPropHelper.h>
#include <blueprint/MessageID.h>
#include <blueprint/Connecting.h>
#include <blueprint/NodeHelper.h>
#include <blueprint/node/Input.h>
#include <blueprint/node/Output.h>
#include <blueprint/node/Function.h>

#include <node0/SceneNode.h>
#include <node0/CompAsset.h>
#include <node0/CompComplex.h>
#include <node2/CompBoundingBox.h>
#include <ns/CompFactory.h>

#include <wx/sizer.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

namespace
{

const wxChar* PIN_IDX_TITLE[] = { wxT("Unknown"), wxT("Bool"), wxT("Vec1"), wxT("Vec2"), wxT("Vec3"), wxT("Vec4"),
                                   wxT("Mat2"), wxT("Mat3"), wxT("Mat4"), wxT("Tex2D"), /*wxT("Tex3D"), */wxT("TexCube"), NULL };

const int PIN_IDX_TO_TYPE[] = {
    bp::PIN_ANY_VAR,

    sg::PIN_BOOLEAN,
    sg::PIN_VECTOR1,
    sg::PIN_VECTOR2,
    sg::PIN_VECTOR3,
    sg::PIN_VECTOR4,
    sg::PIN_MATRIX2,
    sg::PIN_MATRIX3,
    sg::PIN_MATRIX4,
    sg::PIN_TEXTURE2D,
//    sg::PIN_TEXTURE3D,
    sg::PIN_CUBE_MAP,
};

int PinTypeToIdx(int type)
{
    const int num = sizeof(PIN_IDX_TO_TYPE) / sizeof(PIN_IDX_TO_TYPE[0]);
    for (int i = 0; i < num; ++i)
    {
        if (PIN_IDX_TO_TYPE[i] == type) {
            return i;
        }
    }
    assert(0);
    return -1;
}

}

namespace sg
{

WxNodeProperty::WxNodeProperty(wxWindow* parent, const ee0::SubjectMgrPtr& sub_mgr)
	: wxPanel(parent)
	, m_sub_mgr(sub_mgr)
{
	InitLayout();
}

void WxNodeProperty::LoadFromNode(const n0::SceneNodePtr& obj, const bp::NodePtr& node)
{
    m_obj = obj;
	m_node = node;

	m_pg->Clear();

	auto node_type = node->get_type();
	for (auto& prop : node_type.get_properties())
	{
		auto ui_info_obj = prop.get_metadata(ee0::UIMetaInfoTag());
		if (!ui_info_obj.is_valid()) {
			continue;
		}

		auto ui_info = ui_info_obj.get_value<ee0::UIMetaInfo>();
        if ((node_type == rttr::type::get<bp::node::Input>() && ui_info.desc == bp::node::Input::STR_TYPE) ||
            (node_type == rttr::type::get<bp::node::Output>() && ui_info.desc == bp::node::Output::STR_TYPE))
        {
			auto mode_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, PIN_IDX_TITLE);
			auto mode = prop.get_value(node).get_value<int>();
            if (mode < 0) {
                mode = bp::PIN_ANY_VAR;
            }
			mode_prop->SetValue(PinTypeToIdx(mode));
			m_pg->Append(mode_prop);

            continue;
        }

		auto prop_type = prop.get_type();
		if (prop_type == rttr::type::get<PropAngleType>())
		{
			const wxChar* ANGLE_TYPES[] = { wxT("Deg"), wxT("Rad"), NULL };
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, ANGLE_TYPES);
			auto angle_type = prop.get_value(node).get_value<PropAngleType>();
			type_prop->SetValue(static_cast<int>(angle_type));
			m_pg->Append(type_prop);
		}
		else if (prop_type == rttr::type::get<PropMultiChannels>())
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
		else if (prop_type == rttr::type::get<PropBlendMode>())
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
		else if (prop_type == rttr::type::get<PropColorTrans>())
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
		else if (prop_type == rttr::type::get<PropChannelArray>())
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
		else if (prop_type == rttr::type::get<PropMathBaseType>())
		{
			const wxChar* EXP_TYPES[] = { wxT("BaseE"), wxT("Base2"), wxT("Base10"), NULL };
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, EXP_TYPES);
			auto& type = prop.get_value(node).get_value<PropMathBaseType>();
			type_prop->SetValue(static_cast<int>(type));
			m_pg->Append(type_prop);
		}
		else if (prop_type == rttr::type::get<MatrixType>())
		{
			const wxChar* TYPES[] = { wxT("Row"), wxT("Column"), NULL };
			auto type_prop = new wxEnumProperty(ui_info.desc, wxPG_LABEL, TYPES);
			auto& type = prop.get_value(node).get_value<MatrixType>();
			type_prop->SetValue(static_cast<int>(type));
			m_pg->Append(type_prop);
		}
		// utility
		else if (prop_type == rttr::type::get<CmpType>())
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
            ee0::WxPropHelper::CreateProp(m_pg, ui_info, node, prop, [&](const std::string& filepath)
            {
                if (m_node->get_type() == rttr::type::get<bp::node::Function>()) {
                    bp::NodeHelper::LoadFunctionNode(m_obj, m_node);
                }
                m_sub_mgr->NotifyObservers(ee0::MSG_SET_CANVAS_DIRTY);
                m_sub_mgr->NotifyObservers(bp::MSG_BP_NODE_PROP_CHANGED);
            });
		}
	}
}

void WxNodeProperty::InitLayout()
{
	auto sizer = new wxBoxSizer(wxVERTICAL);

	m_pg = new wxPropertyGrid(this, -1, wxDefaultPosition, wxSize(300, 600),
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
	);
    Connect(m_pg->GetId(), wxEVT_PG_CHANGING, wxPropertyGridEventHandler(
        WxNodeProperty::OnPropertyGridChanging));
	Connect(m_pg->GetId(), wxEVT_PG_CHANGED, wxPropertyGridEventHandler(
		WxNodeProperty::OnPropertyGridChanged));
	sizer->Add(m_pg, 1, wxEXPAND);

	SetSizer(sizer);
}

void WxNodeProperty::OnPropertyGridChanging(wxPropertyGridEvent& event)
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
        if (prop.get_metadata(ee0::PropOpenFileTag()).is_valid() && key == ui_info.desc) {
            event.Veto();
            continue;
        }
    }
}

void WxNodeProperty::OnPropertyGridChanged(wxPropertyGridEvent& event)
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
        if (prop.get_metadata(ee0::PropOpenFileTag()).is_valid()) {
            continue;
        }
		auto ui_info_obj = prop.get_metadata(ee0::UIMetaInfoTag());
		if (!ui_info_obj.is_valid()) {
			continue;
		}
		auto ui_info = ui_info_obj.get_value<ee0::UIMetaInfo>();
        if (key == ui_info.desc &&
            ((node_type == rttr::type::get<bp::node::Input>() && ui_info.desc == bp::node::Input::STR_TYPE) ||
             (node_type == rttr::type::get<bp::node::Output>() && ui_info.desc == bp::node::Output::STR_TYPE)))
        {
            prop.set_value(m_node, PIN_IDX_TO_TYPE[wxANY_AS(val, int)]);
            // type deduce
            if (node_type == rttr::type::get<bp::node::Input>()) {
                auto input = std::static_pointer_cast<bp::node::Input>(m_node);
                for (auto& c : input->GetAllOutput()[0]->GetConnecting()) {
                    TypeDeduction::DeduceConn(*c->GetFrom(), *c->GetTo());
                }
            } else if (node_type == rttr::type::get<bp::node::Output>()) {
                auto output = std::static_pointer_cast<bp::node::Output>(m_node);
                for (auto& c : output->GetAllInput()[0]->GetConnecting()) {
                    TypeDeduction::DeduceConn(*c->GetFrom(), *c->GetTo());
                }
            }
            continue;
        }

		auto prop_type = prop.get_type();
		if (prop_type == rttr::type::get<PropAngleType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<PropAngleType>(wxANY_AS(val, int)));
		}
		else if (prop_type == rttr::type::get<PropMultiChannels>() && key == ui_info.desc)
		{
			prop.set_value(m_node, PropMultiChannels(wxANY_AS(val, int)));
		}
		else if (prop_type == rttr::type::get<PropBlendMode>() && key == ui_info.desc)
		{
			prop.set_value(m_node, PropBlendMode(wxANY_AS(val, int)));
		}
		else if (prop_type == rttr::type::get<PropColorTrans>() && (key == "From" || key == "To"))
		{
			auto type = prop.get_value(m_node).get_value<PropColorTrans>();
			if (key == "From") {
				type.from = static_cast<ColorType>(wxANY_AS(val, int));
			} else if (key == "To") {
				type.to = static_cast<ColorType>(wxANY_AS(val, int));
			}
			prop.set_value(m_node, type);
		}
		else if (prop_type == rttr::type::get<PropChannelArray>() && (key == "R" || key == "G" || key == "B" || key == "A"))
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
		else if (prop_type == rttr::type::get<PropMathBaseType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<PropMathBaseType>(wxANY_AS(val, int)));
		}
		else if (prop_type == rttr::type::get<MatrixType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<MatrixType>(wxANY_AS(val, int)));
		}
		else if (prop_type == rttr::type::get<CmpType>() && key == ui_info.desc)
		{
			prop.set_value(m_node, static_cast<CmpType>(wxANY_AS(val, int)));
		}
		else
		{
			ee0::WxPropHelper::UpdateProp(key, val, ui_info, m_node, prop);
		}
	}

	m_node->Refresh();

    // update aabb
    auto& st = m_node->GetStyle();
    m_obj->GetUniqueComp<n2::CompBoundingBox>().SetSize(
        *m_obj, sm::rect(st.width, st.height)
    );

	m_sub_mgr->NotifyObservers(ee0::MSG_SET_CANVAS_DIRTY);
	m_sub_mgr->NotifyObservers(bp::MSG_BP_NODE_PROP_CHANGED);
}

}