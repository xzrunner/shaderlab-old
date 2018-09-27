#pragma once

#include "shadergraph/Node.h"
#include "shadergraph/Pins.h"

namespace sg
{
namespace node
{

class Log : public Node
{
public:
	enum BaseType
	{
		BASE_E = 0,
		BASE_2,
		BASE_10,
	};

public:
	Log()
		: Node("Log", true)
	{
		InitPins({
			{ PINS_DYNAMIC_VECTOR, "In" },
		},{
			{ PINS_DYNAMIC_VECTOR, "Out", }
		});
	}

	virtual void StoreToJson(const std::string& dir, rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(mm::LinearAllocator& alloc, const std::string& dir,
		const rapidjson::Value& val) override;

	BaseType GetType() const { return m_type; }
	void SetType(BaseType type) { m_type = type; }

private:
	BaseType m_type = BASE_E;

	DECLARE_NODE_CLASS(Log)

}; // Log

}
}