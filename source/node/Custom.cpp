#include "shadergraph/node/Custom.h"

namespace sg
{
namespace node
{

Custom::Custom()
    : Node("Custom", false)
{
    InitPins("Custom");
}

void Custom::SetParams(const std::vector<Variant>& params)
{
    m_params = params;

    std::vector<PinsDesc> inputs;
    inputs.reserve(params.size());
    for (auto& p : params) {
        inputs.push_back({ p.type, p.name });
    }
    InitPinsImpl(inputs, true);
    Layout();
}

void Custom::SetReturns(const std::vector<Variant>& returns)
{
    m_returns = returns;

    std::vector<PinsDesc> outputs;
    outputs.reserve(returns.size());
    for (auto& r : returns) {
        outputs.push_back({ r.type, r.name });
    }
    InitPinsImpl(outputs, false);
    Layout();
}

}
}