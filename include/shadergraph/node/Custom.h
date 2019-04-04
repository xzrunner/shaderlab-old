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

    void  SetName(const std::string& name);
    auto& GetName() const { return m_name; }

    auto& GetHeadStr() const { return m_head_str; }
    void  SetHeadStr(const std::string& str) { m_head_str = str; }

    auto& GetBodyStr() const { return m_body_str; }
    void  SetBodyStr(const std::string& str);

    auto& GetInternalStr() const { return m_internal_str; }
    void  SetInternalStr(const std::string& str) { m_internal_str = str; }

    void ResetPorts(const std::vector<PinsDesc>& input,
        const std::vector<PinsDesc>& output);

private:
    static int StrToPinType(const std::string& str);
    static std::string PinTypeToStr(int pin_type);

    std::string GenBodyFromInernal(const std::vector<PinsDesc>& input, 
        const std::vector<PinsDesc>& output) const;

private:
    std::string m_name;

    std::string m_head_str, m_body_str;
    std::string m_internal_str;

	RTTR_ENABLE(Node)

}; // Custom

}
}