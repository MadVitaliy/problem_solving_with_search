#pragma once
#include "PSWS.StateNode/PSWS.StateNode.API.h"

#include <array>
#include <optional>
#include <vector>
#include <memory>
#include <limits>
#include <ostream>

enum class PSWSSTATENODE_API ACTION
{
    LEFT, RIGHT, UP, DOWN, NONE
};

PSWSSTATENODE_API ACTION OppositeAction(const ACTION i_action);

PSWSSTATENODE_API std::ostream& operator<<(std::ostream& io_st, const ACTION& i_action);

PSWSSTATENODE_API std::array<unsigned char, 9> SnakeForm(const std::array<unsigned char, 9>& i_array) noexcept;

PSWSSTATENODE_API std::size_t InversionCount(std::vector<unsigned char> i_vector) noexcept;

class PSWSSTATENODE_API State
{
    friend PSWSSTATENODE_API std::ostream& operator<<(std::ostream& io_st, const State& state);

public:
    State() = default;

    State(const std::array<unsigned char, 9>& i_state) noexcept;

    bool operator==(const State& i_state) const;

    [[nodiscard]] bool NextState(ACTION i_action);

    [[nodiscard]] bool Valid() const;

    [[nodiscard]] bool IsAttainable(const State& i_state) const;

    [[nodiscard]] const std::array<unsigned char, 9>& Get() const;

private:

    [[nodiscard]] std::optional<std::size_t> RightIndex() const noexcept;

    [[nodiscard]] std::optional<std::size_t> LeftIndex() const noexcept;

    [[nodiscard]] std::optional<std::size_t> DownIndex() const noexcept;

    [[nodiscard]] std::optional<std::size_t> UpIndex() const noexcept;

    void SetInvalid();


    std::array<unsigned char, 9> m_state = { 255, 255, 255, 255, 255, 255, 255, 255, 255 };
    std::size_t m_gap_index = std::numeric_limits<std::size_t>::max();
    bool m_valid = false;
};

class PSWSSTATENODE_API Node
{
    friend PSWSSTATENODE_API std::ostream& operator<<(std::ostream& io_st, const Node& state);
public:
    Node() = default;

    explicit Node(const State& i_state, Node* i_parent, ACTION i_parent_action, std::size_t i_node_depth);

    [[nodiscard]] std::size_t Depth() const;
    [[nodiscard]] State& GetState();
    [[nodiscard]] const std::vector<Node*>& GetChildren() const;
    [[nodiscard]] Node* GetParent() const;
    [[nodiscard]] ACTION GetParentAction() const;
    [[nodiscard]] bool PresentInHistory() const;

    Node* AddNode(ACTION i_parent_action, std::size_t i_depth);
    void DeleteChild(Node* i_child);

private:
    [[nodiscard]] bool PresentInHistory(const State& i_state) const;

    State m_state;
    std::size_t m_node_depth = std::numeric_limits<std::size_t>::max();
    Node* m_parent = nullptr;
    ACTION m_parent_action = ACTION::NONE;
    std::vector<Node*> m_children = {};
};