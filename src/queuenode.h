#pragma once

#include "constants.h"
#include "huffman_node.h"

class QueueNode {
public:
    QueueNode(size_t number_entry, CharType symbol, bool is_terminal);
    QueueNode(size_t number_entry, CharType symbol, std::shared_ptr<HuffmanNode> node);
    const size_t GetNumberEntry() const;
    const CharType GetSymbol() const;
    std::shared_ptr<HuffmanNode> GetNode();
    bool operator<(const QueueNode &other) const;

private:
    size_t number_entry_;
    CharType symbol_;
    std::shared_ptr<HuffmanNode> tree_;
};
