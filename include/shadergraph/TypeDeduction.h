#pragma once

namespace bp { class Pin; class Node; }

namespace sg
{

class TypeDeduction
{
public:
    static void DeduceConn(const bp::Pin& p0, const bp::Pin& p1);

    static void DeduceNode(const bp::Node& node);

}; // TypeDeduction

}