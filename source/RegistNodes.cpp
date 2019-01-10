#include "shadergraph/RegistNodes.h"
#include "shadergraph/node/Custom.h"

#include <ee0/ReflectPropTypes.h>

#include <js/RTTR.h>
#include <painting2/RenderSystem.h>
#include <facade/Image.h>
#include <facade/ResPool.h>

#define REGIST_NODE_RTTI(name, prop)                          \
	rttr::registration::class_<sg::node::name>("sg::"#name)   \
		.constructor<>()                                      \
		prop                                                  \
	;

#define PROP
#define REGIST_NODE_RTTI_DEFAULT(name) REGIST_NODE_RTTI(name, PROP)

RTTR_REGISTRATION
{

// artistic
REGIST_NODE_RTTI_DEFAULT(Contrast)
REGIST_NODE_RTTI(Hue,                                                                  \
.property("angle_type", &sg::node::Hue::GetAngleType, &sg::node::Hue::SetAngleType)    \
(                                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("PropAngleType"))             \
)
)
REGIST_NODE_RTTI(InvertColors,                                                                     \
.property("channels", &sg::node::InvertColors::GetChannels, &sg::node::InvertColors::SetChannels)  \
(                                                                                                  \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Channels"))                              \
)
)
REGIST_NODE_RTTI_DEFAULT(ReplaceColor)
REGIST_NODE_RTTI_DEFAULT(Saturation)
REGIST_NODE_RTTI_DEFAULT(WhiteBalance)
REGIST_NODE_RTTI(Blend,                                                  \
.property("mode", &sg::node::Blend::GetMode, &sg::node::Blend::SetMode)  \
(                                                                        \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Mode"))        \
)
)
REGIST_NODE_RTTI_DEFAULT(Gray)
REGIST_NODE_RTTI(ChannelMask,                                                                   \
.property("channels", &sg::node::ChannelMask::GetChannels, &sg::node::ChannelMask::SetChannels) \
(                                                                                               \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Channels"))                           \
)
)
REGIST_NODE_RTTI_DEFAULT(ColorMask)
REGIST_NODE_RTTI_DEFAULT(NormalBlend)
REGIST_NODE_RTTI_DEFAULT(NormalCreate)
REGIST_NODE_RTTI_DEFAULT(NormalStrength)
REGIST_NODE_RTTI_DEFAULT(NormalUnpack)
REGIST_NODE_RTTI_DEFAULT(ColorAddMul)
REGIST_NODE_RTTI_DEFAULT(ColorMap)
REGIST_NODE_RTTI(ColorspaceConversion,                                                        \
.property("type", &sg::node::ColorspaceConversion::GetType, &sg::node::ColorspaceConversion::SetType) \
(                                                                                                     \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("ColTrans"))                                 \
)
)
// channel
REGIST_NODE_RTTI_DEFAULT(Combine)
REGIST_NODE_RTTI(Flip,                                                            \
.property("channels", &sg::node::Flip::GetChannels, &sg::node::Flip::SetChannels) \
(                                                                                 \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Channels"))             \
)
)
REGIST_NODE_RTTI_DEFAULT(Split)
REGIST_NODE_RTTI(Swizzle,                                                               \
.property("channels", &sg::node::Swizzle::GetChannels, &sg::node::Swizzle::SetChannels) \
(                                                                                       \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Channels"))                   \
)
)
// input
REGIST_NODE_RTTI(Boolean,                                                    \
.property("val", &sg::node::Boolean::GetValue, &sg::node::Boolean::SetValue) \
(                                                                            \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vector1B"))        \
)
)
REGIST_NODE_RTTI_DEFAULT(Time)
REGIST_NODE_RTTI(Vector1,                                                  \
.property("x", &sg::node::Vector1::GetValue, &sg::node::Vector1::SetValue) \
(                                                                          \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vector1"))       \
)
)
REGIST_NODE_RTTI(Vector2,                                                    \
.property("x", &sg::node::Vector2::GetX, &sg::node::Vector2::SetX)           \
.property("y", &sg::node::Vector2::GetY, &sg::node::Vector2::SetY)           \
.property("val", &sg::node::Vector2::GetValue, &sg::node::Vector2::SetValue) \
(                                                                            \
	rttr::metadata(js::RTTR::NoSerializeTag(), true),                        \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vector2"))         \
)
)
REGIST_NODE_RTTI(Vector3,                                                    \
.property("x", &sg::node::Vector3::GetX, &sg::node::Vector3::SetX)           \
.property("y", &sg::node::Vector3::GetY, &sg::node::Vector3::SetY)           \
.property("z", &sg::node::Vector3::GetZ, &sg::node::Vector3::SetZ)           \
.property("val", &sg::node::Vector3::GetValue, &sg::node::Vector3::SetValue) \
(                                                                            \
	rttr::metadata(js::RTTR::NoSerializeTag(), true),                        \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vector3"))         \
)
)
REGIST_NODE_RTTI(Vector4,                                                    \
.property("x", &sg::node::Vector4::GetX, &sg::node::Vector4::SetX)           \
.property("y", &sg::node::Vector4::GetY, &sg::node::Vector4::SetY)           \
.property("z", &sg::node::Vector4::GetZ, &sg::node::Vector4::SetZ)           \
.property("w", &sg::node::Vector4::GetW, &sg::node::Vector4::SetW)           \
.property("val", &sg::node::Vector4::GetValue, &sg::node::Vector4::SetValue) \
(                                                                            \
	rttr::metadata(js::RTTR::NoSerializeTag(), true),                        \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vector4"))         \
)
)
REGIST_NODE_RTTI_DEFAULT(CameraPos)
REGIST_NODE_RTTI_DEFAULT(UV)
REGIST_NODE_RTTI(Matrix2,                                                    \
.property("mat", &sg::node::Matrix2::GetValue, &sg::node::Matrix2::SetValue)
)
REGIST_NODE_RTTI(Matrix3,                                                    \
.property("mat", &sg::node::Matrix3::GetValue, &sg::node::Matrix3::SetValue)
)
REGIST_NODE_RTTI(Matrix4,                                                    \
.property("mat", &sg::node::Matrix4::GetValue, &sg::node::Matrix4::SetValue)
)
REGIST_NODE_RTTI_DEFAULT(SampleTex2D)
REGIST_NODE_RTTI(Tex2DAsset,                                                                    \
.property("name", &sg::node::Tex2DAsset::GetName, &sg::node::Tex2DAsset::SetName)               \
(                                                                                               \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Name"))                               \
)                                                                                               \
.property("filepath", &sg::node::Tex2DAsset::GetImagePath, &sg::node::Tex2DAsset::SetImagePath) \
(                                                                                               \
	rttr::metadata(js::RTTR::FilePathTag(), true),                                              \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Filepath")),                          \
	rttr::metadata(ee0::PropOpenFileTag(), ee0::PropOpenFile("*.png"))                          \
)
)
// master
REGIST_NODE_RTTI_DEFAULT(PBR)
REGIST_NODE_RTTI_DEFAULT(Phong)
REGIST_NODE_RTTI_DEFAULT(Raymarching)
REGIST_NODE_RTTI_DEFAULT(Sprite)
// math
REGIST_NODE_RTTI_DEFAULT(Absolute)
REGIST_NODE_RTTI(Exponential,                                                       \
.property("type", &sg::node::Exponential::GetType, &sg::node::Exponential::SetType) \
(                                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Base"))                   \
)
)
REGIST_NODE_RTTI_DEFAULT(Length)
REGIST_NODE_RTTI(Log,                                               \
.property("type", &sg::node::Log::GetType, &sg::node::Log::SetType) \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Base"))   \
)
)
REGIST_NODE_RTTI_DEFAULT(Modulo)
REGIST_NODE_RTTI_DEFAULT(Negate)
REGIST_NODE_RTTI_DEFAULT(Normalize)
REGIST_NODE_RTTI_DEFAULT(Posterize)
REGIST_NODE_RTTI_DEFAULT(Reciprocal)
REGIST_NODE_RTTI_DEFAULT(ReciprocalSquareRoot)
REGIST_NODE_RTTI_DEFAULT(Add)
REGIST_NODE_RTTI_DEFAULT(Divide)
REGIST_NODE_RTTI_DEFAULT(Multiply)
REGIST_NODE_RTTI_DEFAULT(Power)
REGIST_NODE_RTTI_DEFAULT(SquareRoot)
REGIST_NODE_RTTI_DEFAULT(Subtract)
REGIST_NODE_RTTI_DEFAULT(DDX)
REGIST_NODE_RTTI_DEFAULT(DDXY)
REGIST_NODE_RTTI_DEFAULT(DDY)
REGIST_NODE_RTTI_DEFAULT(InverseLerp)
REGIST_NODE_RTTI_DEFAULT(Lerp)
REGIST_NODE_RTTI_DEFAULT(Smoothstep)
REGIST_NODE_RTTI(MatrixConstruction,                                                              \
.property("type", &sg::node::MatrixConstruction::GetType, &sg::node::MatrixConstruction::SetType) \
(                                                                                                 \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Type"))                                 \
)
)
REGIST_NODE_RTTI_DEFAULT(MatrixDeterminant)
REGIST_NODE_RTTI(MatrixSplit,                                                                     \
.property("type", &sg::node::MatrixConstruction::GetType, &sg::node::MatrixConstruction::SetType) \
(                                                                                                 \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Type"))                                 \
)
)
REGIST_NODE_RTTI_DEFAULT(MatrixTranspose)
REGIST_NODE_RTTI_DEFAULT(Clamp)
REGIST_NODE_RTTI_DEFAULT(Fraction)
REGIST_NODE_RTTI_DEFAULT(Maximum)
REGIST_NODE_RTTI_DEFAULT(Minimum)
REGIST_NODE_RTTI_DEFAULT(OneMinus)
REGIST_NODE_RTTI_DEFAULT(RandomRange)
REGIST_NODE_RTTI_DEFAULT(Remap)
REGIST_NODE_RTTI_DEFAULT(Saturate)
REGIST_NODE_RTTI_DEFAULT(Ceiling)
REGIST_NODE_RTTI_DEFAULT(Floor)
REGIST_NODE_RTTI_DEFAULT(Round)
REGIST_NODE_RTTI_DEFAULT(Sign)
REGIST_NODE_RTTI_DEFAULT(Step)
REGIST_NODE_RTTI_DEFAULT(Truncate)
REGIST_NODE_RTTI_DEFAULT(Arccosine)
REGIST_NODE_RTTI_DEFAULT(Arcsine)
REGIST_NODE_RTTI_DEFAULT(Arctangent)
REGIST_NODE_RTTI_DEFAULT(Arctangent2)
REGIST_NODE_RTTI_DEFAULT(Cosine)
REGIST_NODE_RTTI_DEFAULT(DegreesToRadians)
REGIST_NODE_RTTI_DEFAULT(HyperbolicCosine)
REGIST_NODE_RTTI_DEFAULT(HyperbolicSine)
REGIST_NODE_RTTI_DEFAULT(HyperbolicTangent)
REGIST_NODE_RTTI_DEFAULT(RadiansToDegrees)
REGIST_NODE_RTTI_DEFAULT(Sine)
REGIST_NODE_RTTI_DEFAULT(Tangent)
REGIST_NODE_RTTI_DEFAULT(CrossProduct)
REGIST_NODE_RTTI_DEFAULT(Distance)
REGIST_NODE_RTTI_DEFAULT(DotProduct)
REGIST_NODE_RTTI_DEFAULT(Projection)
REGIST_NODE_RTTI_DEFAULT(Rejection)
// procedural
REGIST_NODE_RTTI_DEFAULT(Checkerboard)
REGIST_NODE_RTTI_DEFAULT(Ellipse)
REGIST_NODE_RTTI_DEFAULT(GradientNoise)
REGIST_NODE_RTTI_DEFAULT(Polygon)
REGIST_NODE_RTTI_DEFAULT(Rectangle)
REGIST_NODE_RTTI_DEFAULT(RoundedRectangle)
REGIST_NODE_RTTI_DEFAULT(SimpleNoise)
REGIST_NODE_RTTI_DEFAULT(Voronoi)
// sdf
REGIST_NODE_RTTI_DEFAULT(Intersection)
REGIST_NODE_RTTI_DEFAULT(Subtraction)
REGIST_NODE_RTTI_DEFAULT(Union)
REGIST_NODE_RTTI_DEFAULT(SDF)
REGIST_NODE_RTTI_DEFAULT(Sphere)
REGIST_NODE_RTTI_DEFAULT(Torus)
REGIST_NODE_RTTI_DEFAULT(Box)
REGIST_NODE_RTTI_DEFAULT(EstimateNormal)
REGIST_NODE_RTTI_DEFAULT(PhongIllumination)
// utility
REGIST_NODE_RTTI_DEFAULT(And)
REGIST_NODE_RTTI_DEFAULT(Branch)
REGIST_NODE_RTTI(Comparison,                                      \
(                                                                 \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Type")) \
)
)
REGIST_NODE_RTTI_DEFAULT(Not)
REGIST_NODE_RTTI_DEFAULT(Or)
REGIST_NODE_RTTI_DEFAULT(Preview)
// uv
REGIST_NODE_RTTI(Flipbook,                                                          \
.property("invert", &sg::node::Flipbook::GetInvert, &sg::node::Flipbook::SetInvert) \
(                                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Invert"))                 \
)
)
REGIST_NODE_RTTI_DEFAULT(PolarCoordinates)
REGIST_NODE_RTTI_DEFAULT(RadialShear)
REGIST_NODE_RTTI(Rotate,                                                               \
.property("radians", &sg::node::Rotate::GetAngleType, &sg::node::Rotate::SetAngleType) \
(                                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("PropAngleType"))             \
)
)
REGIST_NODE_RTTI_DEFAULT(Spherize)
REGIST_NODE_RTTI_DEFAULT(TilingAndOffset)
REGIST_NODE_RTTI_DEFAULT(Twirl)
// tools
REGIST_NODE_RTTI(Custom,                                                        \
.property("head", &sg::node::Custom::GetHeadStr, &sg::node::Custom::SetHeadStr) \
(                                                                               \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("HeadStr")),           \
    rttr::metadata(ee0::PropLongStringTag(), true)                              \
)                                                                               \
.property("body", &sg::node::Custom::GetBodyStr, &sg::node::Custom::SetBodyStr) \
(                                                                               \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("BodyStr")),           \
    rttr::metadata(ee0::PropLongStringTag(), true)                              \
)
)

}

namespace sg
{

void nodes_regist_rttr()
{
}

namespace node
{

void Tex2DAsset::Draw(const sm::Matrix2D& mt) const
{
	bp::Node::Draw(mt);

	if (m_img)
	{
		auto model_mat = NodePreview::CalcNodePreviewMat(*this, mt);
		pt2::RenderSystem::DrawTexture(*m_img->GetTexture(), sm::rect(1, 1), model_mat);
	}
}

void Tex2DAsset::SetName(const std::string& name)
{
	m_name = name;
	m_title = m_name;
}

void Tex2DAsset::SetImagePath(std::string filepath)
{
	m_img = facade::ResPool::Instance().Fetch<facade::Image>(std::move(filepath));
}

std::string Tex2DAsset::GetImagePath() const
{
	return m_img ? m_img->GetResPath() : "";
}

}

}