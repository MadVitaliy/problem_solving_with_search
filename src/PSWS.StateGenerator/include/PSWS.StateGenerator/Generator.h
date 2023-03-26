#pragma once
#include "PSWS.StateGenerator/PSWS.StateGenerator.API.h"

#include "PSWS.StateNode/StateNode.h"

#include <array>
#include <optional>
#include <stack>
#include <vector>
#include <memory>
#include <limits>
#include <random>

class Node;

class PSWSSTATEGENERATOR_API StateGenerator
{
public:
    void SetDepth(const std::size_t i_depth);
    State& Get();
    std::vector<ACTION>& GetPath();
    bool Generate();

private:
    bool Generate(Node& io_node);
    std::size_t m_depth_limit = std::numeric_limits<std::size_t>::max();
    State m_generated_state;
    std::vector<ACTION> m_path_to_state;

    std::mt19937 m_random;
};
