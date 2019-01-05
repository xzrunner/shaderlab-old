#include "shadergraph/WxCustomNodePropHelper.h"
#include "shadergraph/WxCustomNodePropEditor.h"
#include "shadergraph/node/Custom.h"

#include <cpputil/StringHelper.h>
#include <node0/SceneNode.h>
#include <node2/CompBoundingBox.h>

#include <wx/propgrid/propgrid.h>

namespace
{

const wxChar* PINS_IDX_TITLE[] = { wxT("Bool"), wxT("Vec1"), wxT("Vec2"), wxT("Vec3"), wxT("Vec4"),
                                   wxT("Mat2"), wxT("Mat3"), wxT("Mat4"), wxT("Tex2D"), /*wxT("Tex3D"), */wxT("TexCube"), NULL };

const sg::PinsType PINS_IDX_TO_TYPE[] = {
    sg::PINS_BOOLEAN,
    sg::PINS_VECTOR1,
    sg::PINS_VECTOR2,
    sg::PINS_VECTOR3,
    sg::PINS_VECTOR4,
    sg::PINS_MATRIX2,
    sg::PINS_MATRIX3,
    sg::PINS_MATRIX4,
    sg::PINS_TEXTURE2D,
//    sg::PINS_TEXTURE3D,
    sg::PINS_CUBE_MAP,
};

const int PINS_TYPE_TO_IDX[] = { 0, -1, 1, 2, 3, 4, -1, 8, 9, -1, 5, 6, 7, -1 };

void add_node_type_prop(wxPropertyGrid* pg, wxPGPropArg parent, const std::string& name,
                        const sg::node::Custom::Variant& var)
{
    auto var_prop = pg->AppendIn(parent, new wxStringProperty(name, wxPG_LABEL, wxT("<composed>")));
    var_prop->SetExpanded(true);

    // name
    pg->AppendIn(var_prop, new wxStringProperty("Name", wxPG_LABEL, var.name.c_str()));

    // type
    pg->AppendIn(var_prop, new wxEnumProperty("Type", wxPG_LABEL, PINS_IDX_TITLE, 0,
        PINS_TYPE_TO_IDX[var.type - sg::PINS_BOOLEAN]));

    // value
    switch (var.type)
    {
    case sg::PINS_BOOLEAN:
        pg->AppendIn(var_prop, new wxBoolProperty("Value", wxPG_LABEL, var.val.b));
        break;
    case sg::PINS_VECTOR1:
        pg->AppendIn(var_prop, new wxFloatProperty("Value", wxPG_LABEL, var.val.vec1));
        break;
    case sg::PINS_VECTOR2:
    {
        auto vec2_prop = pg->AppendIn(var_prop, new wxStringProperty("Value", wxPG_LABEL, wxT("<composed>")));
        vec2_prop->SetExpanded(true);
        pg->AppendIn(vec2_prop, new wxFloatProperty(wxT("X"), wxPG_LABEL, var.val.vec2[0]));
        pg->AppendIn(vec2_prop, new wxFloatProperty(wxT("Y"), wxPG_LABEL, var.val.vec2[1]));
    }
        break;
    case sg::PINS_VECTOR3:
    {
        auto vec3_prop = pg->AppendIn(var_prop, new wxStringProperty("Value", wxPG_LABEL, wxT("<composed>")));
        vec3_prop->SetExpanded(true);
        pg->AppendIn(vec3_prop, new wxFloatProperty(wxT("X"), wxPG_LABEL, var.val.vec3[0]));
        pg->AppendIn(vec3_prop, new wxFloatProperty(wxT("Y"), wxPG_LABEL, var.val.vec3[1]));
        pg->AppendIn(vec3_prop, new wxFloatProperty(wxT("Z"), wxPG_LABEL, var.val.vec3[2]));
    }
        break;
    case sg::PINS_VECTOR4:
    {
        auto vec4_prop = pg->AppendIn(var_prop, new wxStringProperty("Value", wxPG_LABEL, wxT("<composed>")));
        vec4_prop->SetExpanded(true);
        pg->AppendIn(vec4_prop, new wxFloatProperty(wxT("X"), wxPG_LABEL, var.val.vec4[0]));
        pg->AppendIn(vec4_prop, new wxFloatProperty(wxT("Y"), wxPG_LABEL, var.val.vec4[1]));
        pg->AppendIn(vec4_prop, new wxFloatProperty(wxT("Z"), wxPG_LABEL, var.val.vec4[2]));
        pg->AppendIn(vec4_prop, new wxFloatProperty(wxT("W"), wxPG_LABEL, var.val.vec4[3]));
    }
        break;
    case sg::PINS_MATRIX2:
        break;
    case sg::PINS_MATRIX3:
        break;
    case sg::PINS_MATRIX4:
        break;
    default:
        assert(0);
    }
}

void var_changed(const std::vector<std::string>& keys, const wxAny& val, sg::node::Custom::Variant& var)
{
    if (keys[0] == "Name")
    {
        var.name = wxANY_AS(val, wxString);
    }
    else if (keys[0] == "Type")
    {
        var.type = PINS_IDX_TO_TYPE[wxANY_AS(val, int)];
    }
    else if (keys[0] == "Value")
    {
        switch (var.type)
        {
        case sg::PINS_BOOLEAN:
            var.val.b = wxANY_AS(val, bool);
            break;
        case sg::PINS_VECTOR1:
            var.val.vec1 = wxANY_AS(val, float);
            break;
        case sg::PINS_VECTOR2:
            if (keys[1] == "X") {
                var.val.vec2[0] = wxANY_AS(val, float);
            } else if (keys[1] == "Y") {
                var.val.vec2[1] = wxANY_AS(val, float);
            }
            break;
        case sg::PINS_VECTOR3:
            if (keys[1] == "X") {
                var.val.vec3[0] = wxANY_AS(val, float);
            } else if (keys[1] == "Y") {
                var.val.vec3[1] = wxANY_AS(val, float);
            } else if (keys[1] == "Z") {
                var.val.vec3[2] = wxANY_AS(val, float);
            }
            break;
        case sg::PINS_VECTOR4:
            if (keys[1] == "X") {
                var.val.vec4[0] = wxANY_AS(val, float);
            } else if (keys[1] == "Y") {
                var.val.vec4[1] = wxANY_AS(val, float);
            } else if (keys[1] == "Z") {
                var.val.vec4[2] = wxANY_AS(val, float);
            } else if (keys[1] == "W") {
                var.val.vec4[3] = wxANY_AS(val, float);
            }
            break;
        }
    }
}

}

namespace sg
{

void WxCustomNodePropHelper::InitProp(wxPropertyGrid* pg, const n0::SceneNodePtr& obj,
                                      const std::shared_ptr<const node::Custom>& node)
{
    pg->Append(new wxLongStringProperty("Head", wxPG_LABEL, node->GetHeadStr().c_str()));
    pg->Append(new wxLongStringProperty("Body", wxPG_LABEL, node->GetBodyStr().c_str()));

    // pins op btn
    wxPGEditor* pins_btn_editor = new WxCustomNodePropEditor(obj, std::const_pointer_cast<node::Custom>(node));
    static bool registed = false;
    if (!registed) {
        wxPropertyGrid::RegisterEditorClass(pins_btn_editor);
        registed = true;
    }
    pg->Append(new wxPGRootProperty("PinsOP"));
    pg->SetPropertyEditor("PinsOP", pins_btn_editor);

    auto params_prop = pg->Append(new wxStringProperty("Params", wxPG_LABEL, "<composed>"));
    int i = 0;
    for (auto& var : node->GetParams()) {
        add_node_type_prop(pg, params_prop, "Params" + std::to_string(i++), var);
    }

    auto return_prop = pg->Append(new wxStringProperty("Return", wxPG_LABEL, "<composed>"));
    auto& returns = node->GetReturns();
    if (!returns.empty()) {
        add_node_type_prop(pg, return_prop, "Return", returns[0]);
    }
}

void WxCustomNodePropHelper::PropChanged(const wxString& key, const wxAny& val,
                                         const n0::SceneNodePtr& obj, node::Custom& node)
{
    if (key == "Head")
    {
        node.SetHeadStr(wxANY_AS(val, wxString).ToStdString());
        return;
    }
    else if (key == "Body")
    {
        node.SetBodyStr(wxANY_AS(val, wxString).ToStdString());
        return;
    }


    std::vector<std::string> tokens;
    cpputil::StringHelper::Split(key.ToStdString(), ".", tokens);

    if (tokens.size() < 3) {
        return;
    }

    std::vector<std::string> keys;
    std::copy(tokens.begin() + 2, tokens.end(), std::back_inserter(keys));

    if (tokens[0] == "Params")
    {
        auto idx_str = tokens[1].substr(tokens[1].find("Params") + strlen("Params"));
        auto idx = std::stoi(idx_str);
        auto& params = node.GetParams();
        assert(idx >= 0 && idx < static_cast<int>(params.size()));
        var_changed(keys, val, const_cast<node::Custom::Variant&>(params[idx]));
        node.SetParams(node.GetParams());
    }
    else if (tokens[0] == "Return")
    {
        auto& returns = node.GetReturns();
        assert(!returns.empty());
        var_changed(keys, val, const_cast<node::Custom::Variant&>(returns[0]));
        node.SetReturns(node.GetReturns());
    }

    auto& st = node.GetStyle();
    obj->GetUniqueComp<n2::CompBoundingBox>().SetSize(
        *obj, sm::rect(st.width, st.height)
    );
}

}