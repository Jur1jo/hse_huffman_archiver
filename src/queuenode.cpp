#include "queuenode.h"

QueueNode::QueueNode(size_t number_entry, CharType symbol, bool is_terminal)
    : number_entry_(number_entry), symbol_(symbol), tree_(new HuffmanNode(is_terminal, symbol)) {
}

QueueNode::QueueNode(size_t number_entry, CharType symbol, std::shared_ptr<HuffmanNode> node)
    : number_entry_(number_entry), symbol_(symbol), tree_(node) {
}

const size_t QueueNode::GetNumberEntry() const {
    return number_entry_;
}

const CharType QueueNode::GetSymbol() const {
    return symbol_;
}

std::shared_ptr<HuffmanNode> QueueNode::GetNode() {
    return tree_;
}

bool QueueNode::operator<(const QueueNode &other) const {
    return std::make_pair(number_entry_, symbol_) < std::make_pair(other.GetNumberEntry(), other.GetSymbol());
}
