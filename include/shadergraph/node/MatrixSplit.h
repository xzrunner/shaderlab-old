#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class MatrixSplit : public Node
{
public:
	MatrixSplit()
		: Node("MatrixSplit", false)
	{
		InitPins({
			{ PINS_DYNAMIC_MATRIX, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "M0" },
			{ PINS_DYNAMIC_VECTOR, "M1" },
			{ PINS_DYNAMIC_VECTOR, "M2" },
			{ PINS_DYNAMIC_VECTOR, "M3" },
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	void SetRow(bool row) { m_row = row; }
	bool IsRow() const { return m_row; }

	enum OutputID
	{
		ID_M0 = 0,
		ID_M1,
		ID_M2,
		ID_M3,
	};

	DECLARE_NODE_CLASS(MatrixSplit)

private:
	bool m_row = true;

}; // MatrixSplit

}
}