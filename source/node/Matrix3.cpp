#include "shadergraph/node/Matrix3.h"

#include <cpputil/StringHelper.h>

namespace sg
{
namespace node
{

void Matrix3::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                      rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	rapidjson::Value mat_val;
	mat_val.SetArray();
	for (int i = 0; i < 9; ++i) {
		mat_val.PushBack(m_val.x[i], alloc);
	}
	val.AddMember("mat", mat_val, alloc);
}

void Matrix3::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                       const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("mat"));
	auto& mat_val = val["mat"].GetArray();
	sm::mat3 mat;
	for (int i = 0; i < 9; ++i) {
		mat.x[i]= mat_val[i].GetFloat();
	}
	SetValue(mat);
}

}
}