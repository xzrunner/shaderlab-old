#include "shadergraph/ReflectPropTypes.h"
#include "shadergraph/RegistNodes.h"

#include <ee0/ReflectPropTypes.h>

#include <rttr/registration.h>

RTTR_REGISTRATION
{

rttr::registration::class_<sg::Node>("sg::node")
.property("preview", &sg::Node::GetPreview, &sg::Node::SetPreview)
(
    rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Preview"))
)
;

}

namespace bp
{
extern void regist_sm_rttr();
extern void regist_pt0_rttr();
}

namespace sg
{

void regist_rttr()
{
    bp::regist_sm_rttr();
    bp::regist_pt0_rttr();

//	prop_types_regist_rttr();
	nodes_regist_rttr();
}

}
