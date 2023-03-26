#include "PSWS.Search/SearchTree.h"

#include <algorithm>
#include <array>
#include <optional>
#include <iomanip>
#include <iostream>
#include <cassert>


std::size_t DepthSearch::GetNodeMaxCountInMemory() const
{
    return m_node_max_count_in_memory;
}

std::size_t DepthSearch::GetNodeTotalCount() const
{
    return m_node_total_count;
}

void DepthSearch::SetInitialState(const State& i_state)
{
    m_initial_state = Node(i_state, nullptr, ACTION::NONE, 0);
}

void DepthSearch::SetTargetState(const State& i_state)
{
    m_target_state = i_state;
}

void DepthSearch::SetDepth(const std::size_t i_depth)
{
    m_depth_limit = i_depth;
}

std::vector<Node*>& DepthSearch::GetSolution() {
    return m_solution;
}


bool DepthSearch::Run()
{
    if (!m_initial_state.GetState().Valid())
        return false;
    if (!m_target_state.Valid())
        return false;

    bool solution_found = Search(m_initial_state, 0);

    if (solution_found)
        RecoverSolution();

    return solution_found;
}


bool DepthSearch::Search(Node& io_node, std::size_t i_depth)
{
    if (false) {
        std::cout << io_node << std::endl;
    }

    if (io_node.GetState() == m_target_state)
    {
        m_solution.push_back(&io_node);
        return true;
    }

    if (i_depth >= m_depth_limit)
        return false;

    const std::array<ACTION, 4> actions = { ACTION::UP,ACTION::DOWN, ACTION::RIGHT, ACTION::LEFT };
    for (const auto action : actions)
    {
        auto* child_node = io_node.AddNode(action, io_node.Depth() + 1);
        if (!child_node)
            continue;

        ++m_node_total_count;
        ++m_node_current_count;
        m_node_max_count_in_memory = std::max(m_node_max_count_in_memory, m_node_current_count);

        if (Search(*child_node, child_node->Depth()))
            return true;

        io_node.DeleteChild(child_node);
        --m_node_current_count;
    }


    return false;
}

void DepthSearch::RecoverSolution()
{
    Node* parent;
    do
    {
        parent = m_solution.back()->GetParent();
        assert(parent && "nullptr node in solution");
        m_solution.push_back(parent);
    } while (parent != &m_initial_state);

    std::reverse(m_solution.begin(), m_solution.end());
}