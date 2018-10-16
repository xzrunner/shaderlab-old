// artistic
#include "shadergraph/node/ColorAddMul.h"
#include "shadergraph/node/ColorMap.h"
#include "shadergraph/node/Contrast.h"
#include "shadergraph/node/Hue.h"
#include "shadergraph/node/InvertColors.h"
#include "shadergraph/node/ReplaceColor.h"
#include "shadergraph/node/Saturation.h"
#include "shadergraph/node/WhiteBalance.h"
#include "shadergraph/node/Blend.h"
#include "shadergraph/node/Gray.h"
#include "shadergraph/node/ChannelMask.h"
#include "shadergraph/node/ColorMask.h"
#include "shadergraph/node/NormalBlend.h"
#include "shadergraph/node/NormalCreate.h"
#include "shadergraph/node/NormalStrength.h"
#include "shadergraph/node/NormalUnpack.h"
#include "shadergraph/node/ColorspaceConversion.h"
// channel
#include "shadergraph/node/Combine.h"
#include "shadergraph/node/Flip.h"
#include "shadergraph/node/Split.h"
#include "shadergraph/node/Swizzle.h"
// input
#include "shadergraph/node/Boolean.h"
#include "shadergraph/node/Time.h"
#include "shadergraph/node/Vector1.h"
#include "shadergraph/node/Vector2.h"
#include "shadergraph/node/Vector3.h"
#include "shadergraph/node/Vector4.h"
#include "shadergraph/node/UV.h"
#include "shadergraph/node/Matrix2.h"
#include "shadergraph/node/Matrix3.h"
#include "shadergraph/node/Matrix4.h"
#include "shadergraph/node/SampleTex2D.h"
#include "shadergraph/node/Tex2DAsset.h"
// master
#include "shadergraph/node/Phong.h"
#include "shadergraph/node/Sprite.h"
// math
#include "shadergraph/node/Add.h"
#include "shadergraph/node/Divide.h"
#include "shadergraph/node/Multiply.h"
#include "shadergraph/node/Subtract.h"
#include "shadergraph/node/Power.h"
#include "shadergraph/node/SquareRoot.h"
#include "shadergraph/node/Absolute.h"
#include "shadergraph/node/Exponential.h"
#include "shadergraph/node/Length.h"
#include "shadergraph/node/Log.h"
#include "shadergraph/node/Modulo.h"
#include "shadergraph/node/Negate.h"
#include "shadergraph/node/Normalize.h"
#include "shadergraph/node/Posterize.h"
#include "shadergraph/node/Reciprocal.h"
#include "shadergraph/node/ReciprocalSquareRoot.h"
#include "shadergraph/node/DDX.h"
#include "shadergraph/node/DDY.h"
#include "shadergraph/node/DDXY.h"
#include "shadergraph/node/InverseLerp.h"
#include "shadergraph/node/Lerp.h"
#include "shadergraph/node/Smoothstep.h"
#include "shadergraph/node/MatrixConstruction.h"
#include "shadergraph/node/MatrixDeterminant.h"
#include "shadergraph/node/MatrixSplit.h"
#include "shadergraph/node/MatrixTranspose.h"
#include "shadergraph/node/Clamp.h"
#include "shadergraph/node/Fraction.h"
#include "shadergraph/node/Maximum.h"
#include "shadergraph/node/Minimum.h"
#include "shadergraph/node/OneMinus.h"
#include "shadergraph/node/RandomRange.h"
#include "shadergraph/node/Remap.h"
#include "shadergraph/node/Saturate.h"
#include "shadergraph/node/Ceiling.h"
#include "shadergraph/node/Floor.h"
#include "shadergraph/node/Round.h"
#include "shadergraph/node/Sign.h"
#include "shadergraph/node/Step.h"
#include "shadergraph/node/Truncate.h"
#include "shadergraph/node/Arccosine.h"
#include "shadergraph/node/Arcsine.h"
#include "shadergraph/node/Arctangent.h"
#include "shadergraph/node/Arctangent2.h"
#include "shadergraph/node/Cosine.h"
#include "shadergraph/node/DegreesToRadians.h"
#include "shadergraph/node/HyperbolicCosine.h"
#include "shadergraph/node/HyperbolicSine.h"
#include "shadergraph/node/HyperbolicTangent.h"
#include "shadergraph/node/RadiansToDegrees.h"
#include "shadergraph/node/Sine.h"
#include "shadergraph/node/Tangent.h"
#include "shadergraph/node/CrossProduct.h"
#include "shadergraph/node/Distance.h"
#include "shadergraph/node/DotProduct.h"
#include "shadergraph/node/Projection.h"
#include "shadergraph/node/Rejection.h"
// procedural
#include "shadergraph/node/Checkerboard.h"
#include "shadergraph/node/GradientNoise.h"
#include "shadergraph/node/SimpleNoise.h"
#include "shadergraph/node/Voronoi.h"
#include "shadergraph/node/Ellipse.h"
#include "shadergraph/node/Polygon.h"
#include "shadergraph/node/Rectangle.h"
#include "shadergraph/node/RoundedRectangle.h"
// utility
#include "shadergraph/node/Preview.h"
#include "shadergraph/node/And.h"
#include "shadergraph/node/Or.h"
#include "shadergraph/node/Not.h"
#include "shadergraph/node/Branch.h"
#include "shadergraph/node/Comparison.h"
// uv
#include "shadergraph/node/Flipbook.h"
#include "shadergraph/node/PolarCoordinates.h"
#include "shadergraph/node/RadialShear.h"
#include "shadergraph/node/Rotate.h"
#include "shadergraph/node/Spherize.h"
#include "shadergraph/node/TilingAndOffset.h"
#include "shadergraph/node/Twirl.h"

#include <rttr/registration.h>

RTTR_REGISTRATION
{
	// artistic
	rttr::registration::class_<sg::node::ColorAddMul>("sg_col_addmul")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::ColorMap>("sg_col_map")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Contrast>("sg_contrast")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Hue>("sg_hue")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::InvertColors>("sg_invert_colors")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::ReplaceColor>("sg_replace_col")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Saturation>("sg_saturation")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::WhiteBalance>("sg_white_balance")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Blend>("sg_blend")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Gray>("sg_gray")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::ChannelMask>("sg_channel_mask")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::ColorMask>("sg_col_mask")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::NormalBlend>("sg_normal_blend")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::NormalCreate>("sg_normal_create")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::NormalStrength>("sg_normal_strength")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::NormalUnpack>("sg_normal_unpack")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::ColorspaceConversion>("sg_col_conv")
		.constructor<>()
	;
	// channel
	rttr::registration::class_<sg::node::Combine>("sg_combine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Flip>("sg_flip")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Split>("sg_split")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Swizzle>("sg_swizzle")
		.constructor<>()
	;
	// input
	rttr::registration::class_<sg::node::Boolean>("sg_boolean")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Time>("sg_time")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Vector1>("sg_vec1")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Vector2>("sg_vec2")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Vector3>("sg_vec3")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Vector4>("sg_vec4")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::UV>("sg_uv")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Matrix2>("sg_mat2")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Matrix3>("sg_mat3")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Matrix4>("sg_mat4")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::SampleTex2D>("sg_sample_tex2d")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Tex2DAsset>("sg_tex2d_asset")
		.constructor<>()
	;
	// master
	rttr::registration::class_<sg::node::Phong>("sg_phong")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Sprite>("sg_sprite")
		.constructor<>()
	;
	// math
	rttr::registration::class_<sg::node::Add>("sg_add")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Divide>("sg_div")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Multiply>("sg_mul")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Subtract>("sg_sub")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Power>("sg_power")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::SquareRoot>("sg_sqrt")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Absolute>("sg_abs")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Exponential>("sg_exp")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Length>("sg_length")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Log>("sg_log")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Modulo>("sg_mod")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Negate>("sg_neg")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Normalize>("sg_norm")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Posterize>("sg_posterize")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Reciprocal>("sg_reciprocal")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::ReciprocalSquareRoot>("sg_reciprocal_square_root")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::DDX>("sg_ddx")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::DDY>("sg_ddy")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::DDXY>("sg_ddxy")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::InverseLerp>("sg_inverse_lerp")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Lerp>("sg_lerp")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Smoothstep>("sg_smoothstep")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::MatrixConstruction>("sg_mat_construction")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::MatrixDeterminant>("sg_mat_determinant")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::MatrixSplit>("sg_mat_split")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::MatrixTranspose>("sg_mat_transpose")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Clamp>("sg_clamp")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Fraction>("sg_fraction")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Maximum>("sg_max")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Minimum>("sg_min")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::OneMinus>("sg_one_minus")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::RandomRange>("sg_random_range")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Remap>("sg_remap")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Saturate>("sg_saturate")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Ceiling>("sg_ceiling")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Floor>("sg_floor")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Round>("sg_round")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Sign>("sg_sign")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Step>("sg_step")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Truncate>("sg_truncate")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Arccosine>("sg_arccosine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Arcsine>("sg_arcsine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Arctangent>("sg_arctangent")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Arctangent2>("sg_arctangent2")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Cosine>("sg_cosine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::DegreesToRadians>("sg_degrees_to_radians")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::HyperbolicCosine>("sg_hyperbolic_cosine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::HyperbolicSine>("sg_hyperbolic_sine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::HyperbolicTangent>("sg_hyperbolic_tangent")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::RadiansToDegrees>("sg_radians_to_degrees")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Sine>("sg_sine")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Tangent>("sg_tangent")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::CrossProduct>("sg_cross_product")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Distance>("sg_distance")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::DotProduct>("sg_dot_product")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Projection>("sg_projection")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Rejection>("sg_rejection")
		.constructor<>()
	;
	// procedural
	rttr::registration::class_<sg::node::Checkerboard>("sg_checkerboard")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::GradientNoise>("sg_gradient_noise")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::SimpleNoise>("sg_simple_noise")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Voronoi>("sg_voronoi")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Ellipse>("sg_ellipse")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Polygon>("sg_polygon")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Rectangle>("sg_rectangle")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::RoundedRectangle>("sg_rounded_rect")
		.constructor<>()
	;
	// utility
	rttr::registration::class_<sg::node::Preview>("sg_preview")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::And>("sg_and")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Or>("sg_or")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Not>("sg_not")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Branch>("sg_branch")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Comparison>("sg_comparison")
		.constructor<>()
	;
	// uv
	rttr::registration::class_<sg::node::Flipbook>("sg_flipbook")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::PolarCoordinates>("sg_polar_coord")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::RadialShear>("sg_radial_shear")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Rotate>("sg_rotate")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Spherize>("sg_spherize")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::TilingAndOffset>("sg_tiling_and_offset")
		.constructor<>()
	;
	rttr::registration::class_<sg::node::Twirl>("sg_twirl")
		.constructor<>()
	;
}

namespace sg
{

void regist_rttr()
{
}

}
