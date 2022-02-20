//
// Created by Vitaliy on 20.02.2022.
//
#ifndef PROBLEMSOLVINGWITHSEARCH_UTILS_H
#define PROBLEMSOLVINGWITHSEARCH_UTILS_H

#include <array>
#include <optional>
#include <stack>
#include <vector>
#include <memory>
#include <limits>

enum class ACTION
  {
  LEFT, RIGHT, UP, DOWN, NONE
  };


class State
  {
  friend std::ostream &operator<<(std::ostream &io_st, const State &state);

public:
  State() = default;

  State(const std::array<unsigned char, 9> &i_state) noexcept;

  bool operator==(const State &i_state);

  [[nodiscard]] bool NextState(ACTION i_action);

  [[nodiscard]] bool Valid() const;
private:

  [[nodiscard]] std::optional<std::size_t> RightIndex() const noexcept;

  [[nodiscard]] std::optional<std::size_t> LeftIndex() const noexcept;

  [[nodiscard]] std::optional<std::size_t> DownIndex() const noexcept;

  [[nodiscard]] std::optional<std::size_t> UpIndex() const noexcept;

  void SetInvalid();


  std::array<unsigned char, 9> m_state = {255, 255, 255, 255, 255, 255, 255, 255, 255};
  std::size_t m_gap_index = std::numeric_limits<std::size_t>::max();
  bool m_valid = false;
  };

class Node
  {
public:
  Node() = default;

  explicit Node(const State &i_state, Node *i_parent, ACTION i_parent_action, std::size_t i_node_depth);
  State &GetState();
  [[nodiscard]] const std::vector<Node*>& GetChildren() const;
  [[nodiscard]] std::size_t Depth() const;

  Node* AddNode(ACTION i_parent_action, std::size_t i_depth);
  void DeleteChild(Node *i_child);

private:
  std::size_t m_node_depth = std::numeric_limits<std::size_t>::max();
  State m_state;
  Node *m_parent = nullptr;
  ACTION m_parent_action = ACTION::NONE;
  std::vector<Node*> m_children = {};
  };


class DepthSearch
  {
public:
  void SetInitialState(const State &i_state);

  void SetTargetState(const State &i_state);

  void SetDepth(const std::size_t i_depth);

  void Run();
private:
  Node m_initial_state;
  State m_target_state;
  std::size_t m_depth_limit = std::numeric_limits<std::size_t>::max();
  bool Search(Node& io_node, std::size_t i_depth);
  };

#endif //PROBLEMSOLVINGWITHSEARCH_UTILS_H
