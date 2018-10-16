#include "shadergraph/node/MatrixSplit.h"

namespace sg
{
namespace node
{

void MatrixSplit::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                          rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("row", m_row, alloc);
}

void MatrixSplit::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                           const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("row"));
	SetRow(val["row"].GetBool());
}

}
}