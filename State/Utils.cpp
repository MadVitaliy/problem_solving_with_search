//
// Created by Vitaliy on 20.02.2022.
//
#include "Utils.h"

#include <algorithm>
#include <array>
#include <optional>
#include <iomanip>

//State State::GetState()
//  {
//  return State({0, 1, 2, 3, 4, 5, 6, 7, 8});
//  }

State::State(const std::array<unsigned char, 9> &i_state) noexcept
  {
  std::copy(i_state.cbegin(), i_state.cend(), m_state.begin());
  m_valid = true;
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
  m_state = {255, 255, 255, 255, 255, 255, 255, 255, 255};
  m_valid = false;
  }


bool State::Valid() const
  {
  return m_valid;
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


bool State::operator==(const State &i_state)
  {
  return std::equal(m_state.cbegin(), m_state.cend(), i_state.m_state.cbegin());
  }

std::ostream &operator<<(std::ostream &io_st, const State &state)
  {

  std::array<std::size_t, 3> out = {};

  for (std::size_t i = 0; i < state.m_state.size(); ++i)
    out[i] = static_cast<std::size_t>(state.m_state[i]);

  const auto &data = state.m_state;
  io_st << "+-+-+-+\n";
  io_st << '|' << out[0] << '|' << out[1] << '|' << out[2] << "|\n";
  io_st << "+-+-+-+\n";
  io_st << '|' << out[3] << '|' << out[4] << '|' << out[5] << "|\n";
  io_st << "+-+-+-+\n";
  io_st << '|' << out[6] << '|' << out[7] << '|' << out[8] << "|\n";
  io_st << "+-+-+-+\n";
  return io_st;
  }

Node::Node(const State &i_state, Node *i_parent, ACTION i_parent_action, std::size_t i_node_depth) : m_state(i_state),
                                                                                                     m_parent(i_parent),
                                                                                                     m_parent_action(
                                                                                                             i_parent_action),
                                                                                                     m_node_depth(
                                                                                                             i_node_depth)
  {}

State &Node::GetState()
  {
  return m_state;
  }

const std::vector<Node *> &Node::GetChildren() const
  {
  return m_children;
  }

std::size_t Node::Depth() const
  {
  return m_node_depth;
  }

Node *Node::AddNode(ACTION i_parent_action, std::size_t i_depth)
  {
  if (State next_state = m_state; next_state.NextState(i_parent_action))
    {
    auto *child_node = new Node(next_state, this, i_parent_action, i_depth);
    m_children.emplace_back(child_node);
    return child_node;
    }
  return nullptr;
  }

void Node::DeleteChild(Node *i_child)
  {
  auto it_to_delete = std::find(m_children.begin(), m_children.end(), i_child);
  m_children.erase(it_to_delete, it_to_delete + 1);
  }


void DepthSearch::SetInitialState(const State &i_state)
  {
  m_initial_state = Node(i_state, nullptr, ACTION::NONE, 0);
  }

void DepthSearch::SetTargetState(const State &i_state)
  {
  m_target_state = i_state;
  }

void DepthSearch::SetDepth(const std::size_t i_depth)
  {
  m_depth_limit = i_depth;
  }

void DepthSearch::Run()
  {
  if (!m_initial_state.GetState().Valid())
    return;
  if (!m_target_state.Valid())
    return;

  Search(m_initial_state, 0);
  }


bool DepthSearch::Search(Node &io_node, std::size_t i_depth)
  {
  bool found = false;
  if (i_depth > m_depth_limit)
    return false;
  io_node.AddNode(ACTION::UP, io_node.Depth() + 1);
  io_node.AddNode(ACTION::DOWN, io_node.Depth() + 1);
  io_node.AddNode(ACTION::RIGHT, io_node.Depth() + 1);
  io_node.AddNode(ACTION::LEFT, io_node.Depth() + 1);

  for (auto* child: io_node.GetChildren())
    {
    if(!child)
      continue;
    found = 
    }
  if (child_node->GetState() == m_target_state)
    io_node.DeleteChild(child_node);
  return true;
  }