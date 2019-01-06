#include "shadergraph/node/Custom.h"
#include "shadergraph/Pins.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

Custom::Custom()
    : Node("Custom", false)
{
    InitPins("Custom");
}

void Custom::SetBodyStr(const std::string& str)
{
    m_body_str = str;

    std::vector<PinsDesc> inputs, outputs;

    // parse ret type and func name
    auto s_pos = str.find("(");
    std::string head = str.substr(0, s_pos);
    std::vector<std::string> tokens;
    cpputil::StringHelper::Split(head, " ", tokens);
    assert(tokens.size() == 2);
    auto ret_type = TransToPinsType(tokens[0]);
    if (ret_type >= 0) {
        outputs.push_back({ ret_type, "_out" });
    }
    m_title = tokens[1];

    // parse params list
    std::string params_str = str.substr(s_pos + 1, str.find(")") - s_pos - 1);
    std::vector<std::string> params;
    cpputil::StringHelper::Split(params_str, ",", params);
    for (auto& p : params)
    {
        std::vector<std::string> tokens;
        cpputil::StringHelper::Split(p, " ", tokens);
        assert(tokens.size() == 2);
        auto type = TransToPinsType(tokens[0]);
        assert(type >= 0);
        inputs.push_back({ type, tokens[1] });
    }

    InitPins(inputs, outputs);
}

int Custom::TransToPinsType(const std::string& str)
{
    if (str == "void") {
        return -1;
    } else if (str == "float") {
        return PINS_VECTOR1;
    } else if (str == "vec2") {
        return PINS_VECTOR2;
    } else if (str == "vec3") {
        return PINS_VECTOR3;
    } else if (str == "vec4") {
        return PINS_VECTOR4;
    } else if (str == "mat2") {
        return PINS_MATRIX2;
    } else if (str == "mat3") {
        return PINS_MATRIX3;
    } else if (str == "mat4") {
        return PINS_MATRIX4;
    } else {
        assert(0);
        return -1;
    }
}

}
}