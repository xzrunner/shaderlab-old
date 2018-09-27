#include "shadergraph/node/MatrixConstruction.h"

IMPLEMENT_NODE_CLASS(sg::node::MatrixConstruction, sg_mat_construction)

namespace sg
{
namespace node
{

void MatrixConstruction::StoreToJson(const std::string& dir, rapidjson::Value& val,
	                                 rapidjson::MemoryPoolAllocator<>& alloc) const
{
	bp::Node::StoreToJson(dir, val, alloc);

	val.AddMember("row", m_row, alloc);
}

void MatrixConstruction::LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
	                                  const rapidjson::Value& val)
{
	bp::Node::LoadFromJson(alloc, dir, val);

	assert(val.IsObject() && val.HasMember("row"));
	SetRow(val["row"].GetBool());
}

}
}