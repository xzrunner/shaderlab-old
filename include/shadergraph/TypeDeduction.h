#pragma once

namespace bp { class Pins; class Node; }

namespace sg
{

class TypeDeduction
{
public:
    static void DeduceConn(const bp::Pins& p0, const bp::Pins& p1);

    static void DeduceNode(const bp::Node& node);

}; // TypeDeduction

}