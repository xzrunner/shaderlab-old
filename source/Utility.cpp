#include "shadergraph/Utility.h"

#include <cpputil/StringHelper.h>

#include <vector>
#include <cctype>

namespace sg
{

std::string Utility::UnderscoreToCamelCase(const std::string& str)
{
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

std::string Utility::CamelCaseToUnderscore(const std::string& str)
{
    std::vector<std::string> tokens;
    cpputil::StringHelper::Split(str, " ", tokens);

    std::string ret;
    for (auto& sub : tokens)
    {
        if (sub.empty()) {
            continue;
        }
        sub[0] = std::tolower(sub[0]);
        if (!ret.empty()) {
            ret += "_";
        }
        ret += sub;
    }
    return ret;
}

}