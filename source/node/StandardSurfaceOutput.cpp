#include "shaderlab/node/StandardSurfaceOutput.h"
#include "shaderlab/PinType.h"

#include <blueprint/Pin.h>

namespace shaderlab
{
namespace node
{

StandardSurfaceOutput::StandardSurfaceOutput()
    : Node("StandardSurfaceOutput", false)
{
    AddPin(std::make_shared<bp::Pin>(true, 0, PIN_VECTOR3, "Albedo", *this));
    AddPin(std::make_shared<bp::Pin>(true, 1, PIN_VECTOR3, "Normal", *this));
    AddPin(std::make_shared<bp::Pin>(true, 2, PIN_VECTOR3, "Emission", *this));
    AddPin(std::make_shared<bp::Pin>(true, 3, PIN_VECTOR1, "Specular", *this));
    AddPin(std::make_shared<bp::Pin>(true, 4, PIN_VECTOR1, "Gloss", *this));

    AddPin(std::make_shared<bp::Pin>(true, 5, PIN_VECTOR3, "Transmission", *this));
    AddPin(std::make_shared<bp::Pin>(true, 6, PIN_VECTOR3, "Translucency", *this));
    AddPin(std::make_shared<bp::Pin>(true, 7, PIN_VECTOR1, "Refraction", *this));
    AddPin(std::make_shared<bp::Pin>(true, 8, PIN_VECTOR1, "Opacity", *this));
    AddPin(std::make_shared<bp::Pin>(true, 9, PIN_VECTOR1, "Opacity Mask", *this));

    AddPin(std::make_shared<bp::Pin>(true, 10, PIN_VECTOR3, "Custom Lighting", *this));
    AddPin(std::make_shared<bp::Pin>(true, 11, PIN_VECTOR3, "Local Vertex Offset", *this));
    AddPin(std::make_shared<bp::Pin>(true, 12, PIN_VECTOR3, "Local Vertex Position", *this));
    AddPin(std::make_shared<bp::Pin>(true, 13, PIN_VECTOR4, "Tessellation", *this));
    AddPin(std::make_shared<bp::Pin>(true, 14, PIN_VECTOR3, "Debug", *this));

    Layout();
}

}
}