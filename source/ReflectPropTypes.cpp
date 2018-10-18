#include "shadergraph/ReflectPropTypes.h"

#include <rttr/registration.h>

RTTR_REGISTRATION
{
	rttr::registration::enumeration<sg::PropAngleType>("sg_prop_angle_type")
	(
		rttr::value("deg", sg::PropAngleType::DEGREE),
		rttr::value("rad", sg::PropAngleType::RADIAN)
		//rttr::metadata(sg::PropAngleType::DEGREE, "Deg"),
		//rttr::metadata(sg::PropAngleType::RADIAN, "Rad")
	);

	rttr::registration::class_<sg::PropMultiChannels>("sg_prop_multi_channels")
		.property("channels", &sg::PropMultiChannels::channels)
	;

	rttr::registration::class_<sg::PropBlendMode>("sg_prop_blend_mode")
		.property("mode", &sg::PropBlendMode::mode)
	;

	rttr::registration::enumeration<sg::ChannelType>("sg_channel_type")
    (
		rttr::value("r", sg::ChannelType::R),
		rttr::value("g", sg::ChannelType::G),
		rttr::value("b", sg::ChannelType::B),
		rttr::value("a", sg::ChannelType::A)
    );
	rttr::registration::class_<sg::PropChannelArray>("sg_prop_channel_array")
		.property("channels", &sg::PropChannelArray::channels)
	;

	rttr::registration::enumeration<sg::ColorType>("sg_color_type")
    (
		rttr::value("rgb",    sg::ColorType::RGB),
		rttr::value("linear", sg::ColorType::LINEAR),
		rttr::value("hsv",    sg::ColorType::HSV)
    );
	rttr::registration::class_<sg::PropColorTrans>("sg_prop_color_trans")
		.property("from", &sg::PropColorTrans::from)
		.property("to",   &sg::PropColorTrans::to)
	;

	rttr::registration::enumeration<sg::PropMathBaseType>("sg_prop_math_base_type")
    (
		rttr::value("base_e",  sg::PropMathBaseType::BASE_E),
		rttr::value("base_2",  sg::PropMathBaseType::BASE_2),
		rttr::value("base_10", sg::PropMathBaseType::BASE_10)
    );

	rttr::registration::enumeration<sg::MatrixType>("sg_matrix_type")
	(
		rttr::value("row",    sg::MatrixType::ROW),
		rttr::value("column", sg::MatrixType::COLUMN)
	);

	rttr::registration::enumeration<sg::CmpType>("sg_cmp_type")
	(
		rttr::value("equal",            sg::CmpType::EQUAL),
		rttr::value("not_equal",        sg::CmpType::NOT_EQUAL),
		rttr::value("less",             sg::CmpType::LESS),
		rttr::value("less_or_equal",    sg::CmpType::LESS_OR_EQUAL),
		rttr::value("greater",          sg::CmpType::GREATER),
		rttr::value("greater_or_equal", sg::CmpType::GREATER_OR_EQUAL)
	);
}

namespace sg
{
void prop_types_regist_rttr()
{
}
}