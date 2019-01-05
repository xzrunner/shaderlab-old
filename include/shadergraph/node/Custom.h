#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Custom : public Node
{
public:
    struct Variant
    {
        std::string name;

        PinsType type;

        union
        {
            bool  b;
            float vec1;
            float vec2[2];
            float vec3[3];
            float vec4[4];
            // todo tex
            float mat2[4];
            float mat3[9];
            float mat4[16];
        } val;
    };

public:
    Custom();

    auto& GetParams() const { return m_params; }
    void  SetParams(const std::vector<Variant>& params);

    auto& GetReturns() const { return m_returns; }
    void  SetReturns(const std::vector<Variant>& returns);

    auto& GetHeadStr() const { return m_head_str; }
    void  SetHeadStr(const std::string& str) { m_head_str = str; }

    auto& GetBodyStr() const { return m_body_str; }
    void  SetBodyStr(const std::string& str) { m_body_str = str; }

private:
    std::vector<Variant> m_params;
    std::vector<Variant> m_returns;

    std::string m_head_str, m_body_str;

	RTTR_ENABLE(Node)

}; // Custom

}
}