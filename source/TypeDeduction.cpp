#include "shaderlab/TypeDeduction.h"
#include "shaderlab/PinType.h"

#include <blueprint/Pin.h>
#include <blueprint/Node.h>
#include <blueprint/Connecting.h>
#include <blueprint/NodeLayout.h>
#include <blueprint/node/Input.h>
#include <blueprint/node/Output.h>

namespace
{

bool SetPinType(bp::Pin& pin, int type)
{
    assert(type >= 0);

	if (pin.GetType() == type) {
		return false;
	}

	pin.SetType(type);
	for (auto& conn : pin.GetConnecting()) {
		conn->UpdateCurve();
	}

    return true;
}

}

namespace shaderlab
{

void TypeDeduction::DeduceConn(const bp::Pin& p0, const bp::Pin& p1)
{
	int type0 = p0.GetType();
	int type1 = p1.GetType();
	if (type0 == type1) {
		return;
	}

    int old_t0 = p0.GetOldType();
    int old_t1 = p1.GetOldType();
    int new_t0 = type0;
    int new_t1 = type1;
    if (old_t0 == PIN_DYNAMIC_VECTOR || old_t1 == PIN_DYNAMIC_VECTOR)
    {
        if (old_t0 == PIN_DYNAMIC_VECTOR && old_t1 == PIN_DYNAMIC_VECTOR) {
            int max = std::max((int)PIN_VECTOR1, std::min((int)PIN_VECTOR4, std::max(type0, type1)));
            new_t0 = max;
            new_t1 = max;
        } else if (old_t0 == PIN_DYNAMIC_VECTOR) {
            new_t0 = type1;
        } else if (old_t1 == PIN_DYNAMIC_VECTOR) {
            new_t1 = type0;
        }
    }
    else if (old_t0 == PIN_DYNAMIC_MATRIX || old_t1 == PIN_DYNAMIC_MATRIX)
    {
        if (old_t0 == PIN_DYNAMIC_MATRIX && old_t1 == PIN_DYNAMIC_MATRIX) {
            int max = std::max((int)PIN_MATRIX2, std::min((int)PIN_MATRIX4, std::max(type0, type1)));
            new_t0 = max;
            new_t1 = max;
        } else if (old_t0 == PIN_DYNAMIC_MATRIX) {
            new_t0 = type1;
        } else if (old_t1 == PIN_DYNAMIC_MATRIX) {
            new_t1 = type0;
        }
    }
    else if (old_t0 == bp::PIN_ANY_VAR || old_t1 == bp::PIN_ANY_VAR)
    {
        if (old_t0 == bp::PIN_ANY_VAR && old_t1 == bp::PIN_ANY_VAR) {
            int max = std::max(type0, type1);
            new_t0 = max;
            new_t1 = max;
        } else if (old_t0 == bp::PIN_ANY_VAR) {
            new_t0 = type1;
        } else if (old_t1 == bp::PIN_ANY_VAR) {
            new_t1 = type0;
        }

        auto pp0 = p0.GetParent().get_type();
        auto pp1 = p1.GetParent().get_type();
        if (pp0 == rttr::type::get<bp::node::Input>() ||
            pp0 == rttr::type::get<bp::node::Output>()) {
            new_t0 = type0;
        } else if (pp1 == rttr::type::get<bp::node::Input>() ||
                   pp1 == rttr::type::get<bp::node::Output>()) {
            new_t1 = type1;
        }
    }

    SetPinType(const_cast<bp::Pin&>(p0), new_t0);
    DeduceNode(p0.GetParent());

    SetPinType(const_cast<bp::Pin&>(p1), new_t1);
    DeduceNode(p1.GetParent());
}

void TypeDeduction::DeduceNode(const bp::Node& node)
{
    auto node_type = node.get_type();
    if (node_type == rttr::type::get<bp::node::Input>() ||
        node_type == rttr::type::get<bp::node::Output>()) {
        return;
    }

    std::vector<int> in_types, out_types;
    auto& inputs = node.GetAllInput();
    auto& outputs = node.GetAllOutput();
    in_types.resize(inputs.size(), -1);
    out_types.resize(outputs.size(), -1);

    int in_max_vec = -1;
    int in_max_mat = -1;
    int in_max_any = -1;
    for (int i = 0, n = inputs.size(); i < n; ++i)
    {
        auto& pin = inputs[i];
        auto old_type = pin->GetOldType();
        if (old_type == PIN_DYNAMIC_VECTOR ||
            old_type == PIN_DYNAMIC_MATRIX ||
            old_type == bp::PIN_ANY_VAR)
        {
            auto& conns = pin->GetConnecting();
            if (conns.empty())
            {
                in_types[i] = old_type;
            }
            else
            {
                assert(conns.size() == 1);
                auto from = conns[0]->GetFrom();
                auto from_type = from->GetType();
                if (old_type == PIN_DYNAMIC_VECTOR && from_type >= PIN_VECTOR1 && from_type <= PIN_VECTOR4 ||
                    old_type == PIN_DYNAMIC_MATRIX && from_type >= PIN_MATRIX2 && from_type <= PIN_MATRIX4 ||
                    old_type == bp::PIN_ANY_VAR && from_type != bp::PIN_ANY_VAR) {
                    in_types[i] = from_type;
                } else {
                    in_types[i] = old_type;
                }
            }

            switch (old_type)
            {
            case PIN_DYNAMIC_VECTOR:
                if (in_types[i] > in_max_vec) {
                    in_max_vec = in_types[i];
                }
                break;
            case PIN_DYNAMIC_MATRIX:
                if (in_types[i] > in_max_mat) {
                    in_max_mat = in_types[i];
                }
                break;
            case bp::PIN_ANY_VAR:
                if (in_types[i] > in_max_any) {
                    in_max_any = in_types[i];
                }
                break;
            default:
                assert(0);
            }
        }
        else
        {
            in_types[i] = old_type;
        }
    }

    for (int i = 0, n = inputs.size(); i < n; ++i)
    {
        auto& pin = inputs[i];
        auto old_type = pin->GetOldType();
        switch (old_type)
        {
        case PIN_DYNAMIC_VECTOR:
            in_types[i] = in_max_vec;
            break;
        case PIN_DYNAMIC_MATRIX:
            in_types[i] = in_max_mat;
            break;
        case bp::PIN_ANY_VAR:
            in_types[i] = in_max_any;
            break;
        }
    }

    for (int i = 0, n = outputs.size(); i < n; ++i)
    {
        auto& pin = outputs[i];
        auto type = pin->GetType();
        switch (pin->GetOldType())
        {
        case PIN_DYNAMIC_VECTOR:
            if (in_max_vec < 0) {
                out_types[i] = type;
            } else {
                out_types[i] = in_max_vec;
            }
            break;
        case PIN_DYNAMIC_MATRIX:
            if (in_max_mat < 0) {
                out_types[i] = type;
            } else {
                out_types[i] = in_max_mat;
            }
            break;
        case bp::PIN_ANY_VAR:
            if (in_max_any < 0) {
                out_types[i] = type;
            } else {
                out_types[i] = in_max_any;
            }
            break;
        default:
            out_types[i] = type;
        }
    }

    for (int i = 0, n = inputs.size(); i < n; ++i)
    {
        if (SetPinType(*inputs[i], in_types[i]))
        {
            auto& conns = inputs[i]->GetConnecting();
            for (auto& c : conns) {
                DeduceNode(c->GetFrom()->GetParent());
            }
        }
    }
    for (int i = 0, n = outputs.size(); i < n; ++i)
    {
        if (SetPinType(*outputs[i], out_types[i]))
        {
            auto& conns = outputs[i]->GetConnecting();
            for (auto& c : conns) {
                DeduceNode(c->GetTo()->GetParent());
            }
        }
    }

    // pin desc changed
    bp::NodeLayout::UpdateNodeStyle(const_cast<bp::Node&>(node));
    node.SetSizeChanged(true);
}

}