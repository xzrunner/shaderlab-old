#include "shaderlab/ShaderLab.h"
#include "shaderlab/NodeBuilder.h"
#include "shaderlab/Node.h"
#include "shaderlab/PinCallback.h"
#include "shaderlab/TypeDeduction.h"

#include <blueprint/NodeBuilder.h>
#include <blueprint/Pin.h>
#include <blueprint/NodeHelper.h>

#include <shaderweaver/ShaderWeaver.h>

namespace shaderlab
{

CU_SINGLETON_DEFINITION(ShaderLab);

extern void regist_rttr();

ShaderLab::ShaderLab()
{
	sw::ShaderWeaver::Instance();

	regist_rttr();

	Init();
	InitNodes();

    InitPinCallback();
}

void ShaderLab::Init()
{
	bp::NodeBuilder::Callback cb;
	cb.on_created = [](bp::Node& node, std::vector<n0::SceneNodePtr>& nodes) {
		NodeBuilder::CreateDefaultInputs(nodes, node);
	};
	cb.on_connecting = [](bp::Pin& from, bp::Pin& to) {
		bp::NodeHelper::RemoveDefaultNode(to);
	};
	cb.on_connected = [](bp::Pin& from, bp::Pin& to) {
        TypeDeduction::DeduceConn(from, to);
	};
    cb.on_disconnected = [](bp::Pin& from, bp::Pin& to) {
        TypeDeduction::DeduceNode(from.GetParent());
        TypeDeduction::DeduceNode(to.GetParent());
    };
	bp::NodeBuilder::Instance()->RegistCB(cb);
}

void ShaderLab::InitNodes()
{
	auto list = rttr::type::get<Node>().get_derived_classes();
	m_nodes.reserve(list.size());
	for (auto& t : list)
	{
		auto obj = t.create();
		assert(obj.is_valid());
		auto node = obj.get_value<bp::NodePtr>();
		assert(node);
		m_nodes.push_back(node);
	}
}

}