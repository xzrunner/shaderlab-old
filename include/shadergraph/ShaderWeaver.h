#pragma once

#include <node0/typedef.h>
#include <sw/typedef.h>
#include <unirender/VertexAttrib.h>

#include <vector>

namespace ur { class Shader; }
namespace sw { class Node; }
namespace bp { class Node; }

namespace sg
{

// shader graph -> shader weaver -> shader string
class ShaderWeaver
{
public:
	ShaderWeaver(const std::vector<n0::SceneNodePtr>& nodes,
		const std::string& type);

	std::shared_ptr<ur::Shader> CreateShader() const;

private:
	sw::NodePtr CreateWeaverNode(const bp::Node& node);
	sw::NodePtr CreateInputChild(const bp::Node& node, int input_idx);

private:
	bool m_debug_print;

	std::vector<sw::NodePtr> m_cached_nodes;

	std::vector<sw::NodePtr> m_vert_nodes;
	sw::NodePtr m_frag_node = nullptr;

	std::vector<ur::VertexAttrib> m_layout;

	// textures
	std::vector<std::string> m_texture_names;
	std::vector<uint32_t>    m_texture_ids;

}; // ShaderWeaver

}