#include "shadergraph/Node.h"
#include "shadergraph/NodePreview.h"
#include "shadergraph/Pins.h"

#include <shaderweaver/Node.h>
#include <cpputil/StringHelper.h>

#include <cctype>

namespace sg
{

Node::Node(const std::string& title, bool preview, bool debug_print)
	: bp::Node(title)
{
	if (preview) {
		m_preview = std::make_unique<NodePreview>(*this, debug_print);
	}
}

void Node::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);
	if (m_preview) {
		m_preview->Draw(mt);
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

void Node::InitPins(const std::vector<PinsDesc>& input,
	                const std::vector<PinsDesc>& output)
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

	auto sw2sg = [](std::vector<PinsDesc>& dst, const std::vector<sw::Node::Port>& src)
	{
		dst.resize(src.size());
		for (int i = 0, n = src.size(); i < n; ++i)
		{
			auto& s = src[i];
			auto& d = dst[i];
			auto& t = s.var.GetType();
			if (t.precision == sw::VT_BOOL) {
				d.type = PINS_BOOLEAN;
			} else if (t.precision == sw::VT_FLT && t.dim == sw::VT_1) {
				d.type = PINS_VECTOR1;
			} else if (t.precision == sw::VT_FLT && t.dim == sw::VT_2) {
				d.type = PINS_VECTOR2;
			} else if (t.precision == sw::VT_FLT && t.dim == sw::VT_3) {
				d.type = PINS_VECTOR3;
            } else if (t.precision == sw::VT_FLT && t.dim == sw::VT_4) {
                d.type = PINS_VECTOR4;
            } else if (t.precision == sw::VT_FLT && t.dim == 0) {
                d.type = PINS_DYNAMIC_VECTOR;
			} else if (t.interp == sw::VT_T2D) {
				d.type = PINS_TEXTURE2D;
			} else if (t.interp == sw::VT_TCUBE) {
				d.type = PINS_CUBE_MAP;
			} else if (t.interp == sw::VT_MAT && t.dim == sw::VT_2) {
				d.type = PINS_MATRIX2;
			} else if (t.interp == sw::VT_MAT && t.dim == sw::VT_3) {
				d.type = PINS_MATRIX3;
            } else if (t.interp == sw::VT_MAT && t.dim == sw::VT_4) {
                d.type = PINS_MATRIX4;
            } else if (t.interp == sw::VT_MAT && t.dim == 0) {
                d.type = PINS_DYNAMIC_MATRIX;
			} else if (t.interp == sw::VT_FUNC) {
				d.type = PINS_FUNCTION;
			}
			// todo PINS_DYNAMIC_VECTOR PINS_COLOR PINS_DYNAMIC_MATRIX

			auto& name = s.var.GetName();
			d.name = UnderscoreToCamelCase(name);
		}
	};

	std::vector<PinsDesc> input, output;
	sw2sg(input, imports);
	sw2sg(output, exports);

	InitPins(input, output);
}

void Node::InitPinsImpl(const std::vector<PinsDesc>& pins, bool is_input)
{
	auto& dst = is_input ? m_all_input : m_all_output;
	dst.clear();
	dst.reserve(pins.size());
	int idx = 0;
	for (auto& d : pins)
	{
		auto p = std::make_shared<Pins>(is_input, idx++, d.type, d.name, *this);
		if (!CheckPinsName(*p, dst)) {
			assert(0);
			return;
		}
		dst.push_back(p);
	}
}

std::string Node::UnderscoreToCamelCase(const std::string& str)
{
	if (str == "_in") {
		return "In";
	} else if (str == "_out") {
		return "Out";
	} else if (str == "rgba") {
		return "RGBA";
	} else if (str == "uv") {
		return "UV";
	}

	std::vector<std::string> tokens;
	cpputil::StringHelper::Split(str, "_", tokens);

	std::string ret;
	for (auto& sub : tokens)
	{
		if (sub.empty()) {
			continue;
		}
		sub[0] = std::toupper(sub[0]);
		if (!ret.empty()) {
			ret += " ";
		}
		ret += sub;
	}
	return ret;
}

}