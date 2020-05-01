#include "shaderlab/ReflectPropTypes.h"

#include <rttr/registration.h>

RTTR_REGISTRATION
{

rttr::registration::enumeration<shaderlab::PropAngleType>("sg_prop_angle_type")
(
	rttr::value("deg", shaderlab::PropAngleType::DEGREE),
	rttr::value("rad", shaderlab::PropAngleType::RADIAN)
	//rttr::metadata(shaderlab::PropAngleType::DEGREE, "Deg"),
	//rttr::metadata(shaderlab::PropAngleType::RADIAN, "Rad")
);

rttr::registration::class_<shaderlab::PropMultiChannels>("sg_prop_multi_channels")
	.property("channels", &shaderlab::PropMultiChannels::channels)
;

rttr::registration::class_<shaderlab::PropBlendMode>("sg_prop_blend_mode")
	.property("mode", &shaderlab::PropBlendMode::mode)
;

rttr::registration::enumeration<shaderlab::ChannelType>("sg_channel_type")
(
	rttr::value("r", shaderlab::ChannelType::R),
	rttr::value("g", shaderlab::ChannelType::G),
	rttr::value("b", shaderlab::ChannelType::B),
	rttr::value("a", shaderlab::ChannelType::A)
);
rttr::registration::class_<shaderlab::PropChannelArray>("sg_prop_channel_array")
	.property("channels", &shaderlab::PropChannelArray::channels)
;

rttr::registration::enumeration<shaderlab::ColorType>("sg_color_type")
(
	rttr::value("rgb",    shaderlab::ColorType::RGB),
	rttr::value("linear", shaderlab::ColorType::LINEAR),
	rttr::value("hsv",    shaderlab::ColorType::HSV)
);
rttr::registration::class_<shaderlab::PropColorTrans>("sg_prop_color_trans")
	.property("from", &shaderlab::PropColorTrans::from)
	.property("to",   &shaderlab::PropColorTrans::to)
;

rttr::registration::enumeration<shaderlab::PropMathBaseType>("sg_prop_math_base_type")
(
	rttr::value("base_e",  shaderlab::PropMathBaseType::BASE_E),
	rttr::value("base_2",  shaderlab::PropMathBaseType::BASE_2),
	rttr::value("base_10", shaderlab::PropMathBaseType::BASE_10)
);

rttr::registration::enumeration<shaderlab::MatrixType>("sg_matrix_type")
(
	rttr::value("row",    shaderlab::MatrixType::ROW),
	rttr::value("column", shaderlab::MatrixType::COLUMN)
);

rttr::registration::enumeration<shaderlab::CmpType>("sg_cmp_type")
(
	rttr::value("equal",            shaderlab::CmpType::EQUAL),
	rttr::value("not_equal",        shaderlab::CmpType::NOT_EQUAL),
	rttr::value("less",             shaderlab::CmpType::LESS),
	rttr::value("less_or_equal",    shaderlab::CmpType::LESS_OR_EQUAL),
	rttr::value("greater",          shaderlab::CmpType::GREATER),
	rttr::value("greater_or_equal", shaderlab::CmpType::GREATER_OR_EQUAL)
);

rttr::registration::enumeration<shaderlab::ViewSpace>("sg_view_space")
(
	rttr::value("Object",  shaderlab::ViewSpace::Object),
	rttr::value("View",    shaderlab::ViewSpace::View),
	rttr::value("World",   shaderlab::ViewSpace::World),
	rttr::value("Tangent", shaderlab::ViewSpace::Tangent)
);

}

namespace shaderlab
{
void prop_types_regist_rttr()
{
}
}