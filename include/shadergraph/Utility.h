#pragma once

#include <string>

namespace sg
{

class Utility
{
public:
    static std::string UnderscoreToCamelCase(const std::string& str);
    static std::string CamelCaseToUnderscore(const std::string& str);

}; // Utility

}