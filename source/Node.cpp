#include "shadergraph/Node.h"
#include "shadergraph/NodePreview.h"
#include "shadergraph/Utility.h"
#include "shadergraph/PinType.h"

#include <blueprint/Pin.h>

#include <shaderweaver/Node.h>
#include <node2/RenderSystem.h>

namespace sg
{

Node::Node(const std::string& title, bool preview,
           bool debug_print, bool use_rt)
	: bp::Node(title)
{
	if (preview) {
		m_preview = std::make_unique<NodePreview>(*this, debug_print, use_rt);
	}
}

void Node::Draw(const n2::RenderParams& rp) const
{
	bp::Node::Draw(rp);
	if (m_preview) {
		m_preview->Draw(rp.GetMatrix());
	}
}

bool Node::Update(const bp::UpdateParams& params)
{
	bool ret = bp::Node::Update(params);
	if (m_preview) {
		if (m_preview->Update(params)) {
			ret = true;
		}
	}
	return ret;
}

void Node::SetPreview(bool preview)
{
    if (GetPreview() == preview) {
        return;
    }

    if (preview) {
        m_preview = std::make_unique<NodePreview>(*this, false);
    } else {
        m_preview.reset();
        int zz = 0;
    }
}

bool Node::GetPreview() const
{
    return m_preview != nullptr;
}

void Node::InitPins(const std::vector<PinDesc>& input,
	                const std::vector<PinDesc>& output)
{
	InitPinsImpl(input, true);
	InitPinsImpl(output, false);
	Layout();
}

void Node::InitPins(const std::string& name)
{
	rttr::type t = rttr::type::get_by_name("sw::" + name);
	rttr::variant var = t.create();
	assert(var.is_valid());

	auto method_imports = t.get_method("GetImports");
	assert(method_imports.is_valid());
	auto var_imports = method_imports.invoke(var);
	assert(var_imports.is_valid()
		&& var_imports.is_type<std::vector<sw::Node::Port>>());
	auto& imports = var_imports.get_value<std::vector<sw::Node::Port>>();

	auto method_exports = t.get_method("GetExports");
	assert(method_exports.is_valid());
	auto var_exports = method_exports.invoke(var);
	assert(var_exports.is_valid()
		&& var_exports.is_type<std::vector<sw::Node::Port>>());
	auto& exports = var_exports.get_value<std::vector<sw::Node::Port>>();

	auto sw2sg = [](std::vector<PinDesc>& dst, const std::vector<sw::Node::Port>& src)
	{
		dst.resize(src.size());
		for (int i = 0, n = src.size(); i < n; ++i)
		{
			auto& s = src[i];
			auto& d = dst[i];
			auto& t = s.var.GetType();
			if (t.precision == sw::VT_BOOL) {
				d.type = PIN_BOOLEAN;
			} else if (t.precision == sw::VT_FLT && t.dim == sw::VT_1) {
				d.type = PIN_VECTOR1;
			} else if (t.precision == sw::VT_FLT && t.dim == sw::VT_2) {
				d.type = PIN_VECTOR2;
			} else if (t.precision == sw::VT_FLT && t.dim == sw::VT_3) {
				d.type = PIN_VECTOR3;
            } else if (t.precision == sw::VT_FLT && t.dim == sw::VT_4) {
                d.type = PIN_VECTOR4;
            } else if (t.precision == sw::VT_FLT && t.dim == 0) {
                d.type = PIN_DYNAMIC_VECTOR;
			} else if (t.interp == sw::VT_T2D) {
				d.type = PIN_TEXTURE2D;
			} else if (t.interp == sw::VT_TCUBE) {
				d.type = PIN_CUBE_MAP;
			} else if (t.interp == sw::VT_MAT && t.dim == sw::VT_2) {
				d.type = PIN_MATRIX2;
			} else if (t.interp == sw::VT_MAT && t.dim == sw::VT_3) {
				d.type = PIN_MATRIX3;
            } else if (t.interp == sw::VT_MAT && t.dim == sw::VT_4) {
                d.type = PIN_MATRIX4;
            } else if (t.interp == sw::VT_MAT && t.dim == 0) {
                d.type = PIN_DYNAMIC_MATRIX;
			} else if (t.interp == sw::VT_FUNC) {
				d.type = PIN_FUNCTION;
			} else if (t.precision == 0 && t.dim == 0 && t.interp == 0) {
                d.type = bp::PIN_ANY_VAR;
            }
			// todo PIN_DYNAMIC_VECTOR PIN_COLOR PIN_DYNAMIC_MATRIX

			auto& name = s.var.GetName();
			d.name = PortNameFromVar(name);
		}
	};

	std::vector<PinDesc> input, output;
	sw2sg(input, imports);
	sw2sg(output, exports);

	InitPins(input, output);
}

void Node::InitPinsImpl(const std::vector<PinDesc>& pins, bool is_input)
{
	auto& dst = is_input ? m_all_input : m_all_output;
	dst.clear();
	dst.reserve(pins.size());
	int idx = 0;
	for (auto& d : pins)
	{
		auto p = std::make_shared<bp::Pin>(is_input, idx++, d.type, d.name, *this);
		if (!CheckPinName(*p, dst)) {
			assert(0);
			return;
		}
		dst.push_back(p);
	}
}

std::string Node::PortNameFromVar(const std::string& str)
{
	if (str == "_in") {
		return "In";
	} else if (str == "_out") {
		return "Out";
	} else if (str == "rgba") {
		return "RGBA";
	} else if (str == "uv") {
		return "UV";
    } else {
        return Utility::UnderscoreToCamelCase(str);
    }
}

}