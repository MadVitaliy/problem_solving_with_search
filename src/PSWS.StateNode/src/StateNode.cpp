#include "PSWS.StateNode/StateNode.h"

#include <algorithm>
#include <array>
#include <optional>
#include <iomanip>
#include <iostream>
#include <cassert>

std::array<unsigned char, 9>  SnakeForm(const std::array<unsigned char, 9>& i_array) noexcept
{
    std::array<unsigned char, 9> snake = i_array;
    for (std::size_t i = 1; i < 3; i += 2)
        std::reverse(snake.begin() + i * 3, snake.begin() + (i + 1) * 3);
    return snake;
}

std::size_t InversionCount(std::vector<unsigned char> i_vector) noexcept
{
    std::size_t inversion_counter = 0;
    for (std::size_t i = 0; i < i_vector.size(); ++i)
        for (std::size_t j = i + 1; j < i_vector.size(); ++j)
            if (i_vector[i] > i_vector[j])
                ++inversion_counter;

    return inversion_counter;
}

ACTION OppositeAction(const ACTION i_action)
{
    switch (i_action)
    {
    case ACTION::LEFT:
        return ACTION::RIGHT;
    case ACTION::RIGHT:
        return ACTION::LEFT;
    case ACTION::UP:
        return ACTION::DOWN;
    case ACTION::DOWN:
        return ACTION::UP;
    case ACTION::NONE:
        return ACTION::NONE;
    }
    return ACTION::NONE;
}

State::State(const std::array<unsigned char, 9>& i_state) noexcept : m_valid(true)
{
    std::copy(i_state.cbegin(), i_state.cend(), m_state.begin());
    const auto it = std::find(m_state.cbegin(), m_state.cend(), 0);
    m_gap_index = std::distance(m_state.cbegin(), it);
}

std::optional<std::size_t> State::RightIndex() const noexcept
{
    if (!m_valid)
        return std::nullopt;
    return ((m_gap_index + 1) % 3 != 0) ? std::make_optional(m_gap_index + 1) : std::nullopt;
}

std::optional<std::size_t> State::LeftIndex() const noexcept
{
    if (!m_valid)
        return std::nullopt;
    return m_gap_index % 3 != 0 ? std::make_optional(m_gap_index - 1) : std::nullopt;
}

std::optional<std::size_t> State::DownIndex() const noexcept
{
    if (!m_valid)
        return std::nullopt;
    return m_gap_index < 3 * 3 - 3 ? std::make_optional(m_gap_index + 3) : std::nullopt;
}

std::optional<std::size_t> State::UpIndex() const noexcept
{
    if (!m_valid)
        return std::nullopt;
    return m_gap_index >= 3 ? std::make_optional(m_gap_index - 3) : std::nullopt;
}

void State::SetInvalid()
{
    m_state = { 255, 255, 255, 255, 255, 255, 255, 255, 255 };
    m_valid = false;
}


bool State::Valid() const
{
    return m_valid;
}

bool State::IsAttainable(const State& i_state) const
{
    const auto snake1 = SnakeForm(m_state);
    const auto snake2 = SnakeForm(i_state.m_state);

    const auto  inversion_count1 = InversionCount({ snake1.begin(), snake1.end() });
    const auto  inversion_count2 = InversionCount({ snake2.begin(), snake2.end() });

    {
        std::cout << "State1:\n" << *this << std::endl;
        std::cout << "State2:\n" << i_state << std::endl;

        std::cout << "Snake1:\n";
        for (const auto number : snake1)
            std::cout << static_cast<std::size_t>(number) << ' ';
        std::cout << "\nInversion count: " << inversion_count1 << std::endl << std::endl;

        std::cout << "Snake2:\n";
        for (const auto number : snake2)
            std::cout << static_cast<std::size_t>(number) << ' ';
        std::cout << "\nInversion count: " << inversion_count2 << std::endl << std::endl;

    }
    return inversion_count1 % 2 == inversion_count2 % 2;
}

const std::array<unsigned char, 9>& State::Get() const
{
    return m_state;
}

bool State::NextState(ACTION i_action)
{
    std::optional<std::size_t> puzzle_to_move_index;
    switch (i_action)
    {
    case ACTION::LEFT:
        puzzle_to_move_index = RightIndex();
        break;
    case ACTION::RIGHT:
        puzzle_to_move_index = LeftIndex();
        break;
    case ACTION::UP:
        puzzle_to_move_index = DownIndex();
        break;
    case ACTION::DOWN:
        puzzle_to_move_index = UpIndex();
        break;
    case ACTION::NONE:
        puzzle_to_move_index = std::nullopt;
        break;
    }
    if (!puzzle_to_move_index)
    {
        return false;
    }
    std::swap(m_state[m_gap_index], m_state[puzzle_to_move_index.value()]);
    m_gap_index = puzzle_to_move_index.value();
    return true;
}


bool State::operator==(const State& i_state) const
{
    return std::equal(m_state.cbegin(), m_state.cend(), i_state.m_state.cbegin());
}

std::ostream& operator<<(std::ostream& io_st, const State& state)
{

    std::array<std::size_t, 9> out = {};

    for (std::size_t i = 0; i < state.m_state.size(); ++i)
        out[i] = static_cast<std::size_t>(state.m_state[i]);

    const auto& data = state.m_state;
    io_st << "+-+-+-+\n";
    io_st << '|' << out[0] << '|' << out[1] << '|' << out[2] << "|\n";
    io_st << "+-+-+-+\n";
    io_st << '|' << out[3] << '|' << out[4] << '|' << out[5] << "|\n";
    io_st << "+-+-+-+\n";
    io_st << '|' << out[6] << '|' << out[7] << '|' << out[8] << "|\n";
    io_st << "+-+-+-+\n";
    return io_st;
}

std::ostream& operator<<(std::ostream& io_st, const ACTION& i_action)
{
    switch (i_action)
    {
    case ACTION::LEFT:
        io_st << "LEFT";
        break;
    case ACTION::RIGHT:
        io_st << "RIGHT";
        break;
    case ACTION::UP:
        io_st << "UP";
        break;
    case ACTION::DOWN:
        io_st << "DOWN";
        break;
    case ACTION::NONE:
        io_st << "NONE";
        break;
    }
    return io_st;
}

std::ostream& operator<<(std::ostream& io_st, const Node& i_node)
{
    io_st << "Node depth: " << i_node.m_node_depth << std::endl;
    io_st << "Node parent: " << reinterpret_cast<std::size_t>(i_node.m_parent) << std::endl;
    io_st << "Node parent action: " << i_node.m_parent_action << std::endl;
    io_st << "State:\n" << i_node.m_state << std::endl;
    return io_st;
}

Node::Node(const State& i_state, Node* i_parent, ACTION i_parent_action, std::size_t i_node_depth) :
    m_state(i_state),
    m_node_depth(i_node_depth),
    m_parent(i_parent),
    m_parent_action(i_parent_action)
{}

State& Node::GetState()
{
    return m_state;
}

const std::vector<Node*>& Node::GetChildren() const
{
    return m_children;
}

Node* Node::GetParent() const
{
    return m_parent;
}

ACTION Node::GetParentAction() const
{
    return m_parent_action;
}

bool Node::PresentInHistory(const State& i_state) const
{
    if (!m_parent)
        return false;
    return m_parent->PresentInHistory(i_state);
}

bool Node::PresentInHistory() const
{
    if (!m_parent)
        return false;
    return m_parent->PresentInHistory(m_state);
}

std::size_t Node::Depth() const
{
    return m_node_depth;
}

Node* Node::AddNode(ACTION i_parent_action, std::size_t i_depth)
{
    State next_state = m_state;
    if (!next_state.NextState(i_parent_action))
        return nullptr;

    auto* child_node = new Node(next_state, this, i_parent_action, i_depth);
    m_children.emplace_back(child_node);
    return child_node;
}

void Node::DeleteChild(Node* i_child)
{
    auto it_to_delete = std::find(m_children.begin(), m_children.end(), i_child);
    Node* child_node = *it_to_delete;
    delete child_node;
    m_children.erase(it_to_delete, it_to_delete + 1);
}