#include "PSWS.StateGenerator/Generator.h"

#include <algorithm>
#include <array>
#include <optional>
#include <iomanip>
#include <iostream>
#include <cassert>


namespace
{
    bool erase(std::vector<ACTION>& io_actions, const ACTION i_action)
    {
        const auto action_it = std::find(io_actions.begin(), io_actions.end(), i_action);
        if (action_it == io_actions.end())
            return false;
        io_actions.erase(action_it, action_it + 1);
        return true;

    }
}

void StateGenerator::SetDepth(const std::size_t i_depth)
{
    m_depth_limit = i_depth;
    m_path_to_state.resize(i_depth + 1);
}

State& StateGenerator::Get()
{
    return m_generated_state;
}

std::vector<ACTION>& StateGenerator::GetPath()
{
    return m_path_to_state;
}

bool StateGenerator::Generate()
{
    m_random.seed(clock());
    auto* initial_node = new Node(State({ 0,1,2,3,4,5,6,7,8 }), nullptr, ACTION::NONE, 0);
    const auto generated = Generate(*initial_node);
    assert(initial_node);
    delete initial_node;

    std::reverse(m_path_to_state.begin(), m_path_to_state.end());
    for (auto& action : m_path_to_state)
        action = OppositeAction(action);

    return  generated;
}

bool StateGenerator::Generate(Node& io_node)
{
    if (false) {
        std::cout << io_node << std::endl;
    }
    m_path_to_state[io_node.Depth()] = io_node.GetParentAction();
    if (io_node.PresentInHistory())
        return false;

    if (io_node.Depth() == m_depth_limit)
    {
        m_generated_state = io_node.GetState();
        return true;
    }

    std::vector actions = { ACTION::UP,ACTION::DOWN, ACTION::RIGHT, ACTION::LEFT };
    bool generated = false;
    do
    {
        erase(actions, OppositeAction(io_node.GetParentAction()));
        ACTION next_action = actions[m_random() % actions.size()];


        State node_state_copy = io_node.GetState();

        if (!node_state_copy.NextState(next_action))
            continue;

        auto* next_node = new Node(node_state_copy, &io_node, next_action, io_node.Depth() + 1);
        generated = Generate(*next_node);
        delete next_node;
        if (generated)
            break;
    } while (!actions.empty());

    return generated;
}