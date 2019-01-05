#pragma once

#include <node0/typedef.h>

#include <memory>

class wxPropertyGrid;
class wxString;
class wxAny;

namespace sg
{

namespace node { class Custom; }

class WxCustomNodePropHelper
{
public:
    static void InitProp(wxPropertyGrid* pg, const n0::SceneNodePtr& obj,
        const std::shared_ptr<const node::Custom>& node);

    static void PropChanged(const wxString& key, const wxAny& val,
        const n0::SceneNodePtr& obj, node::Custom& node);

}; // WxCustomNodePropHelper

}