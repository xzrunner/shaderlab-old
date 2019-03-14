#pragma once

#include <SM_Vector.h>

#include <array>
#include <string>

namespace sg
{

enum class PropAngleType
{
	DEGREE = 0,
	RADIAN,
};

struct PropMultiChannels
{
	PropMultiChannels(uint32_t channels = 0)
		: channels(channels) {}

	static const uint32_t CHANNEL_R = 0x1;
	static const uint32_t CHANNEL_G = 0x2;
	static const uint32_t CHANNEL_B = 0x4;
	static const uint32_t CHANNEL_A = 0x8;

	uint32_t channels = 0;
};

struct PropBlendMode
{
	PropBlendMode(uint32_t mode) : mode(mode) {}

	uint32_t mode;
};

enum class ChannelType
{
	R = 0,
	G,
	B,
	A
};

struct PropChannelArray
{
	static const size_t CHANNEL_COUNT = 4;
	std::array<ChannelType, CHANNEL_COUNT> channels = {
		ChannelType::R,
		ChannelType::G,
		ChannelType::B,
		ChannelType::A
	};
};

enum class ColorType
{
	RGB = 0,
	LINEAR,
	HSV,
};

struct PropColorTrans
{
	PropColorTrans(ColorType f, ColorType t)
		: from(f), to(t) {}

	ColorType from, to;
};

enum class PropMathBaseType
{
	BASE_E = 0,
	BASE_2,
	BASE_10,
};

enum class MatrixType
{
	ROW = 0,
	COLUMN
};

enum class CmpType
{
	EQUAL = 0,
	NOT_EQUAL,
	LESS,
	LESS_OR_EQUAL,
	GREATER,
	GREATER_OR_EQUAL,
};

enum class ViewSpace
{
    Object = 0,
    View,
    World,
    Tangent
};

void prop_types_regist_rttr();

}