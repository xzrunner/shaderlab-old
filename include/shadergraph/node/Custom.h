#pragma once

#include "shadergraph/Node.h"

namespace sg
{
namespace node
{

class Custom : public Node
{
public:
    Custom();

    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }

    auto& GetHeadStr() const { return m_head_str; }
    void  SetHeadStr(const std::string& str) { m_head_str = str; }

    auto& GetBodyStr() const { return m_body_str; }
    void  SetBodyStr(const std::string& str);

    void ResetPorts(const std::vector<PinsDesc>& input,
        const std::vector<PinsDesc>& output);

private:
    static int TransToPinsType(const std::string& str);

private:
    std::string m_name;

    std::string m_head_str, m_body_str;

	RTTR_ENABLE(Node)

}; // Custom

}
}