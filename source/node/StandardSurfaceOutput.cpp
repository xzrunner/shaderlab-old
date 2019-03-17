#include "shadergraph/node/StandardSurfaceOutput.h"
#include "shadergraph/PinsType.h"

#include <blueprint/Pins.h>

namespace sg
{
namespace node
{

StandardSurfaceOutput::StandardSurfaceOutput()
    : Node("StandardSurfaceOutput", false)
{
    AddPins(std::make_shared<bp::Pins>(true, 0, PINS_VECTOR3, "Albedo", *this));
    AddPins(std::make_shared<bp::Pins>(true, 1, PINS_VECTOR3, "Normal", *this));
    AddPins(std::make_shared<bp::Pins>(true, 2, PINS_VECTOR3, "Emission", *this));
    AddPins(std::make_shared<bp::Pins>(true, 3, PINS_VECTOR1, "Specular", *this));
    AddPins(std::make_shared<bp::Pins>(true, 4, PINS_VECTOR1, "Gloss", *this));

    AddPins(std::make_shared<bp::Pins>(true, 5, PINS_VECTOR3, "Transmission", *this));
    AddPins(std::make_shared<bp::Pins>(true, 6, PINS_VECTOR3, "Translucency", *this));
    AddPins(std::make_shared<bp::Pins>(true, 7, PINS_VECTOR1, "Refraction", *this));
    AddPins(std::make_shared<bp::Pins>(true, 8, PINS_VECTOR1, "Opacity", *this));
    AddPins(std::make_shared<bp::Pins>(true, 9, PINS_VECTOR1, "Opacity Mask", *this));

    AddPins(std::make_shared<bp::Pins>(true, 10, PINS_VECTOR3, "Custom Lighting", *this));
    AddPins(std::make_shared<bp::Pins>(true, 11, PINS_VECTOR3, "Local Vertex Offset", *this));
    AddPins(std::make_shared<bp::Pins>(true, 12, PINS_VECTOR3, "Local Vertex Position", *this));
    AddPins(std::make_shared<bp::Pins>(true, 13, PINS_VECTOR4, "Tessellation", *this));
    AddPins(std::make_shared<bp::Pins>(true, 14, PINS_VECTOR3, "Debug", *this));

    Layout();
}

}
}