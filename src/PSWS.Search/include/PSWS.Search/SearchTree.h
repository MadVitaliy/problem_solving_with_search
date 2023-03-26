#pragma once
#include "PSWS.Search/PSWS.Search.API.h"

#include "PSWS.StateNode/StateNode.h"

#include <vector>
#include <limits>

class PSWSSEARCH_API DepthSearch
{
public:
    void SetInitialState(const State& i_state);

    void SetTargetState(const State& i_state);

    void SetDepth(const std::size_t i_depth);

    std::size_t GetNodeMaxCountInMemory() const;

    std::size_t GetNodeTotalCount() const;

    std::vector<Node*>& GetSolution();

    bool Run();
private:
    bool Search(Node& io_node, std::size_t i_depth);
    void RecoverSolution();
    Node m_initial_state;
    State m_target_state;
    std::size_t m_depth_limit = std::numeric_limits<std::size_t>::max();
    std::vector<Node*> m_solution;

    std::size_t m_node_current_count = 1;
    std::size_t m_node_total_count = 1;
    std::size_t m_node_max_count_in_memory = 1;
};
