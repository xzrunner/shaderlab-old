#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/ReflectPropTypes.h"
#include "shadergraph/PinsType.h"

#include <shaderweaver/node/Blend.h>
#include <cpputil/StringHelper.h>

namespace sg
{

void nodes_regist_rttr();

namespace node
{

#define SG_DEFINE_NODE(name, preview, debug, rt, prop)   \
class name : public Node                                 \
{                                                        \
public:                                                  \
	name()                                               \
		: Node(#name, preview, debug, rt)                \
	{                                                    \
		InitPins(#name);                                 \
	}                                                    \
                                                         \
	prop                                                 \
	RTTR_ENABLE(Node)                                    \
};

#define SG_NODE_PROP
#define SG_DEFINE_NODE_DEFAULT(name)    SG_DEFINE_NODE(name, false, false, false, SG_NODE_PROP)
#define SG_DEFINE_NODE_PREVIEW(name)    SG_DEFINE_NODE(name, true,  false, false, SG_NODE_PROP)
#define SG_DEFINE_NODE_PREVIEW_RT(name) SG_DEFINE_NODE(name, true,  false, true,  SG_NODE_PROP)
#define SG_DEFINE_NODE_DEBUG(name)      SG_DEFINE_NODE(name, false, true,  false, SG_NODE_PROP)

// artistic
SG_DEFINE_NODE_PREVIEW(Contrast)
SG_DEFINE_NODE(Hue, true, false, false,                      \
	auto GetAngleType() const { return m_type; }             \
	void SetAngleType(PropAngleType type) { m_type = type; } \
private:                                                     \
	PropAngleType m_type = PropAngleType::RADIAN;
)
SG_DEFINE_NODE(InvertColors, true, false, false,                                    \
	auto& GetChannels() const { return m_channels; }                                \
	void SetChannels(const PropMultiChannels& channels) { m_channels = channels; }  \
private:                                                                            \
	PropMultiChannels m_channels = 0;                                               \
)
SG_DEFINE_NODE_PREVIEW(ReplaceColor)
SG_DEFINE_NODE_PREVIEW(Saturation)
SG_DEFINE_NODE_PREVIEW(WhiteBalance)
SG_DEFINE_NODE(Blend, true, false, false,                \
	auto GetMode() const { return m_mode.mode; }         \
	void SetMode(uint32_t mode) { m_mode.mode = mode; }  \
private:                                                 \
	PropBlendMode m_mode = sw::node::Blend::MODE_BURN;   \
)
SG_DEFINE_NODE_PREVIEW(Gray)
SG_DEFINE_NODE(ChannelMask, true, false, false,          \
	auto& GetChannels() const { return m_channels; }     \
	void SetChannels(const PropMultiChannels& channels); \
private:                                                 \
	PropMultiChannels m_channels =                       \
		PropMultiChannels::CHANNEL_R |                   \
		PropMultiChannels::CHANNEL_G |                   \
		PropMultiChannels::CHANNEL_B |                   \
		PropMultiChannels::CHANNEL_A;                    \
)
SG_DEFINE_NODE_PREVIEW(ColorMask)
SG_DEFINE_NODE_PREVIEW(NormalBlend)
SG_DEFINE_NODE_PREVIEW(NormalCreate)
SG_DEFINE_NODE_PREVIEW(NormalStrength)
SG_DEFINE_NODE_PREVIEW(NormalUnpack)
SG_DEFINE_NODE_PREVIEW(ColorAddMul)
SG_DEFINE_NODE_PREVIEW(ColorMap)
SG_DEFINE_NODE(ColorspaceConversion, true, false, false,                    \
	auto& GetType() const { return m_type; }                                \
	void SetType(const PropColorTrans& type) { m_type = type; }             \
private:                                                                    \
	PropColorTrans m_type = PropColorTrans(ColorType::RGB, ColorType::RGB); \
)
SG_DEFINE_NODE_PREVIEW(RGBToHSV)
SG_DEFINE_NODE_PREVIEW(HSVToRGB)
// channel
SG_DEFINE_NODE_PREVIEW(Combine)
SG_DEFINE_NODE(Flip, true, false, false,                                           \
	auto& GetChannels() const { return m_channels; }                               \
	void SetChannels(const PropMultiChannels& channels) { m_channels = channels; } \
private:                                                                           \
	PropMultiChannels m_channels = 0;                                              \
)
SG_DEFINE_NODE_PREVIEW(Split)
SG_DEFINE_NODE(Swizzle, true, false, false,                                       \
	auto& GetChannels() const { return m_channels; }                              \
	void SetChannels(const PropChannelArray& channels) { m_channels = channels; } \
private:                                                                          \
	PropChannelArray m_channels;                                                  \
)
// input
class Boolean : public Node
{
public:
	Boolean() : Node("Boolean", false) {
		InitPins("Boolean");
		UpdateTitle();
	}
	virtual void Refresh() override { UpdateTitle(); }
    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }
	auto GetValue() const { return m_val; }
	void SetValue(bool val) {
		m_val = val;
		UpdateTitle();
	}
private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = m_val ? "true" : "false";
	}
private:
    std::string m_name;
	bool m_val = true;
	RTTR_ENABLE(Node)
}; // Boolean
SG_DEFINE_NODE_DEFAULT(Time)
class Vector1 : public Node
{
public:
	Vector1() : Node("Vector1", false) {
		InitPins("Vector1");
		UpdateTitle();
	}
	virtual void Refresh() override { UpdateTitle(); }
    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }
	auto GetValue() const { return m_val; }
	void SetValue(float val) {
		m_val = val;
		UpdateTitle();
	}
private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val, 2);
	}
private:
    std::string m_name;
	float m_val = 0;
	RTTR_ENABLE(Node)
}; // Vector1
class Vector2 : public Node
{
public:
	Vector2() : Node("Vector2", false) {
		InitPins("Vector2");
		UpdateTitle();
	}
	virtual void Refresh() override { UpdateTitle(); }
    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }
	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec2& val) {
		m_val = val;
		UpdateTitle();
	}
	// for serialize with rttr
	float GetX() const { return m_val.x; }
	void SetX(float x) { m_val.x = x; UpdateTitle(); }
	float GetY() const { return m_val.y; }
	void SetY(float y) { m_val.y = y; UpdateTitle(); }
private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.y, 2);
	}
private:
    std::string m_name;
	sm::vec2 m_val;
	RTTR_ENABLE(Node)
}; // Vector2
class Vector3 : public Node
{
public:
	Vector3() : Node("Vector3", false) {
		InitPins("Vector3");
		UpdateTitle();
	}
	virtual void Refresh() override { UpdateTitle(); }
    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }
	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec3& val) {
		m_val = val;
		UpdateTitle();
	}
	// for serialize with rttr
	float GetX() const { return m_val.x; }
	void SetX(float x) { m_val.x = x; UpdateTitle(); }
	float GetY() const { return m_val.y; }
	void SetY(float y) { m_val.y = y; UpdateTitle(); }
	float GetZ() const { return m_val.z; }
	void SetZ(float z) { m_val.z = z; UpdateTitle(); }
private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.y, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.z, 2);
	}
private:
    std::string m_name;
	sm::vec3 m_val;
	RTTR_ENABLE(Node)
}; // Vector3
class Vector4 : public Node
{
public:
	Vector4() : Node("Vector4", false) {
		InitPins("Vector4");
		UpdateTitle();
	}
	virtual void Refresh() override { UpdateTitle(); }
    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }
	auto& GetValue() const { return m_val; }
	void SetValue(const sm::vec4& val) {
		m_val = val;
		UpdateTitle();
	}
	// for serialize with rttr
	float GetX() const { return m_val.x; }
	void SetX(float x) { m_val.x = x; UpdateTitle(); }
	float GetY() const { return m_val.y; }
	void SetY(float y) { m_val.y = y; UpdateTitle(); }
	float GetZ() const { return m_val.z; }
	void SetZ(float z) { m_val.z = z; UpdateTitle(); }
	float GetW() const { return m_val.w; }
	void SetW(float w) { m_val.w = w; UpdateTitle(); }
private:
	void UpdateTitle() {
		SetStyleSmallTitleFont(true);
		m_title = cpputil::StringHelper::ToString(m_val.x, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.y, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.z, 2) + ", " +
				  cpputil::StringHelper::ToString(m_val.w, 2);
	}
private:
    std::string m_name;
	sm::vec4 m_val;
	RTTR_ENABLE(Node)
}; // Vector4
SG_DEFINE_NODE_DEFAULT(CameraPos)
SG_DEFINE_NODE_DEFAULT(TexCoords)
SG_DEFINE_NODE_DEFAULT(TextureTransform)
class UV : public Node
{
public:
	UV() : Node("UV", false)
	{
		// todo channel
		SetName("v_texcoord");      // todozz1234
		InitPins("UV");
	}
    void  SetName(const std::string& name) { m_name = name; }
    auto& GetName() const { return m_name; }
private:
    std::string m_name;
	RTTR_ENABLE(Node)
}; // UV
SG_DEFINE_NODE(ViewDirection, false, false, false,                                     \
    ViewSpace GetViewSpace() const { return m_view_space; }                            \
    void SetViewSpace(ViewSpace view_space) { m_view_space = view_space; }             \
    bool GetSafeNormalize() const { return m_safe_normalize; }                         \
    void SetSafeNormalize(bool safe_normalize) { m_safe_normalize = safe_normalize; }  \
private:                                                                               \
    ViewSpace m_view_space;                                                            \
    bool m_safe_normalize = false;                                                     \
)
SG_DEFINE_NODE_DEFAULT(IndirectDiffuseLighting)
SG_DEFINE_NODE_DEFAULT(IndirectSpecularLight)
SG_DEFINE_NODE_DEFAULT(LightAttenuation)
SG_DEFINE_NODE_DEFAULT(LightColor)
SG_DEFINE_NODE_DEFAULT(WorldSpaceLightDir)
SG_DEFINE_NODE(Matrix2, false, false, false,                  \
    void  SetName(const std::string& name) { m_name = name; } \
    auto& GetName() const { return m_name; }                  \
	auto& GetValue() const { return m_val; }                  \
	void SetValue(const sm::mat2& val) { m_val = val; }       \
private:                                                      \
    std::string m_name;                                       \
	sm::mat2 m_val;                                           \
)
SG_DEFINE_NODE(Matrix3, false, false, false,                  \
    void  SetName(const std::string& name) { m_name = name; } \
    auto& GetName() const { return m_name; }                  \
	auto& GetValue() const { return m_val; }                  \
	void SetValue(const sm::mat3& val) { m_val = val; }       \
private:                                                      \
    std::string m_name;                                       \
	sm::mat3 m_val;                                           \
)
SG_DEFINE_NODE(Matrix4, false, false, false,                  \
    void  SetName(const std::string& name) { m_name = name; } \
    auto& GetName() const { return m_name; }                  \
	auto& GetValue() const { return m_val; }                  \
	void SetValue(const sm::mat4& val) { m_val = val; }       \
private:                                                      \
    std::string m_name;                                       \
	sm::mat4 m_val;                                           \
)
SG_DEFINE_NODE_DEFAULT(Color)
SG_DEFINE_NODE_DEFAULT(PI)
SG_DEFINE_NODE_DEFAULT(WorldBitangent)
SG_DEFINE_NODE_DEFAULT(WorldPosition)
SG_DEFINE_NODE_DEFAULT(WorldTangent)
SG_DEFINE_NODE_DEFAULT(VertexBitangent)
SG_DEFINE_NODE_DEFAULT(VertexNormal)
SG_DEFINE_NODE_DEFAULT(VertexTangent)
SG_DEFINE_NODE_PREVIEW(SampleTex2D)
SG_DEFINE_NODE_PREVIEW(SampleTex3D)
SG_DEFINE_NODE_PREVIEW(SampleTriplanar)
SG_DEFINE_NODE_DEFAULT(UnpackScaleNormal)
// master
SG_DEFINE_NODE_DEFAULT(PBR)
SG_DEFINE_NODE_DEFAULT(Phong)
SG_DEFINE_NODE_PREVIEW_RT(Raymarching)
class Sprite : public Node
{
public:
	Sprite()
		: Node("Sprite", false)
	{
		InitPins({
			{ PINS_TEXTURE2D, "Tex" },
			{ PINS_VECTOR3,   "Mul" },
			{ PINS_VECTOR3,   "Add" },
		},{
		});
	}

public:
	enum InputID
	{
		ID_TEX = 0,
		ID_COL_MUL,
		ID_COL_ADD,
	};

	RTTR_ENABLE(Node)

}; // Sprite
// math
SG_DEFINE_NODE_PREVIEW(Absolute)
SG_DEFINE_NODE(Exponential, true, false, false,            \
	PropMathBaseType GetType() const { return m_type; }    \
	void SetType(PropMathBaseType type) { m_type = type; } \
private:                                                   \
	PropMathBaseType m_type = PropMathBaseType::BASE_E;    \
)
SG_DEFINE_NODE_PREVIEW(Length)
SG_DEFINE_NODE(Log, true, false, false,                    \
	PropMathBaseType GetType() const { return m_type; }    \
	void SetType(PropMathBaseType type) { m_type = type; } \
private:                                                   \
	PropMathBaseType m_type = PropMathBaseType::BASE_E;    \
)
SG_DEFINE_NODE_PREVIEW(Modulo)
SG_DEFINE_NODE_PREVIEW(Negate)
SG_DEFINE_NODE_PREVIEW(Normalize)
SG_DEFINE_NODE_PREVIEW(Posterize)
SG_DEFINE_NODE_PREVIEW(Reciprocal)
SG_DEFINE_NODE_PREVIEW(ReciprocalSquareRoot)
class Add : public Node
{
public:
    Add() : Node("Add", true) {
        InitPins("Add");
        SetExtensibleInputPorts(true);
	}
	RTTR_ENABLE(Node)
}; // Add
SG_DEFINE_NODE_PREVIEW(Divide)
class Multiply : public Node
{
public:
    Multiply() : Node("Multiply", true) {
        InitPins("Multiply");
        SetExtensibleInputPorts(true);
	}
	RTTR_ENABLE(Node)
}; // Multiply
SG_DEFINE_NODE_PREVIEW(Power)
SG_DEFINE_NODE_PREVIEW(SquareRoot)
SG_DEFINE_NODE_PREVIEW(Subtract)
SG_DEFINE_NODE_DEFAULT(DDX)
SG_DEFINE_NODE_DEFAULT(DDXY)
SG_DEFINE_NODE_DEFAULT(DDY)
SG_DEFINE_NODE_DEFAULT(FWidth)
SG_DEFINE_NODE_PREVIEW(InverseLerp)
SG_DEFINE_NODE_PREVIEW(Lerp)
SG_DEFINE_NODE_PREVIEW(Smoothstep)
SG_DEFINE_NODE(MatrixConstruction, false, false, false, \
	void SetType(MatrixType type) { m_type = type; }    \
	MatrixType GetType() const { return m_type; }       \
private:                                                \
	MatrixType m_type = MatrixType::ROW;                \
)
SG_DEFINE_NODE_DEFAULT(MatrixDeterminant)
SG_DEFINE_NODE_DEFAULT(MatrixInverse)
SG_DEFINE_NODE(MatrixSplit, false, false, false,     \
	void SetType(MatrixType type) { m_type = type; } \
	MatrixType GetType() const { return m_type; }    \
private:                                             \
	MatrixType m_type = MatrixType::ROW;             \
)
SG_DEFINE_NODE_DEFAULT(MatrixTranspose)
SG_DEFINE_NODE_PREVIEW(Clamp)
SG_DEFINE_NODE_PREVIEW(Fraction)
SG_DEFINE_NODE_PREVIEW(Maximum)
SG_DEFINE_NODE_PREVIEW(Minimum)
SG_DEFINE_NODE_PREVIEW(OneMinus)
SG_DEFINE_NODE_PREVIEW(RandomRange)
SG_DEFINE_NODE_PREVIEW(Remap)
SG_DEFINE_NODE_PREVIEW(Saturate)
SG_DEFINE_NODE_PREVIEW(Ceiling)
SG_DEFINE_NODE_PREVIEW(Floor)
SG_DEFINE_NODE_PREVIEW(Round)
SG_DEFINE_NODE_PREVIEW(Sign)
SG_DEFINE_NODE_PREVIEW(Step)
SG_DEFINE_NODE_PREVIEW(Truncate)
SG_DEFINE_NODE_PREVIEW(Arccosine)
SG_DEFINE_NODE_PREVIEW(Arcsine)
SG_DEFINE_NODE_PREVIEW(Arctangent)
SG_DEFINE_NODE_PREVIEW(Arctangent2)
SG_DEFINE_NODE_PREVIEW(Cosine)
SG_DEFINE_NODE_PREVIEW(DegreesToRadians)
SG_DEFINE_NODE_PREVIEW(HyperbolicCosine)
SG_DEFINE_NODE_PREVIEW(HyperbolicSine)
SG_DEFINE_NODE_PREVIEW(HyperbolicTangent)
SG_DEFINE_NODE_PREVIEW(RadiansToDegrees)
SG_DEFINE_NODE_PREVIEW(Sine)
SG_DEFINE_NODE_PREVIEW(Tangent)
SG_DEFINE_NODE_PREVIEW(CrossProduct)
SG_DEFINE_NODE_PREVIEW(Distance)
SG_DEFINE_NODE_PREVIEW(DotProduct)
SG_DEFINE_NODE_PREVIEW(Projection)
SG_DEFINE_NODE_PREVIEW(Rejection)
SG_DEFINE_NODE_PREVIEW(TransformDirection)
SG_DEFINE_NODE_PREVIEW(ScaleAndOffset)
// procedural
SG_DEFINE_NODE_PREVIEW(Checkerboard)
SG_DEFINE_NODE_PREVIEW(Ellipse)
SG_DEFINE_NODE_PREVIEW(GradientNoise)
SG_DEFINE_NODE_PREVIEW(Polygon)
SG_DEFINE_NODE_PREVIEW(Rectangle)
SG_DEFINE_NODE_PREVIEW(RoundedRectangle)
SG_DEFINE_NODE_PREVIEW(SimpleNoise)
SG_DEFINE_NODE_PREVIEW(Voronoi)
// sdf
SG_DEFINE_NODE_DEFAULT(Intersection)
SG_DEFINE_NODE_DEFAULT(Subtraction)
SG_DEFINE_NODE_DEFAULT(Union)
SG_DEFINE_NODE_DEFAULT(SDF)
SG_DEFINE_NODE_DEFAULT(Sphere)
SG_DEFINE_NODE_DEFAULT(Torus)
SG_DEFINE_NODE_DEFAULT(Box)
SG_DEFINE_NODE_DEFAULT(EstimateNormal)
SG_DEFINE_NODE_DEFAULT(PhongIllumination)
// tools
SG_DEFINE_NODE_PREVIEW(Relay)
// utility
SG_DEFINE_NODE_DEFAULT(And)
SG_DEFINE_NODE_DEFAULT(Branch)
SG_DEFINE_NODE(Comparison, false, false, false,   \
	auto GetType() const { return m_type; }       \
	void SetType(CmpType type) { m_type = type; } \
private:                                          \
	CmpType m_type = CmpType::EQUAL;              \
)
SG_DEFINE_NODE_DEFAULT(Not)
SG_DEFINE_NODE_DEFAULT(Or)
SG_DEFINE_NODE_DEFAULT(ViewMatrix)
SG_DEFINE_NODE_DEFAULT(WorldNormalVector)
SG_DEFINE_NODE_DEFAULT(DecodeFloatRGBA)
SG_DEFINE_NODE_DEFAULT(EncodeFloatRGBA)
SG_DEFINE_NODE_DEFAULT(VertexToFragment)
// uv
SG_DEFINE_NODE(Flipbook, true, false, false,                       \
	auto& GetInvert() const { return m_invert; }                   \
	void SetInvert(const sm::bvec2& invert) { m_invert = invert; } \
private:                                                           \
	sm::bvec2 m_invert = sm::bvec2(false, false);                  \
)
SG_DEFINE_NODE_PREVIEW(PolarCoordinates)
SG_DEFINE_NODE_PREVIEW(RadialShear)
SG_DEFINE_NODE(Rotate, true, false, false,                   \
	auto GetAngleType() const { return m_type; }             \
	void SetAngleType(PropAngleType type) { m_type = type; } \
private:                                                     \
	PropAngleType m_type = PropAngleType::RADIAN;            \
)
SG_DEFINE_NODE_PREVIEW(Spherize)
SG_DEFINE_NODE_PREVIEW(TilingAndOffset)
SG_DEFINE_NODE_PREVIEW(Twirl)
// anim
SG_DEFINE_NODE_PREVIEW(Skin)

}
}