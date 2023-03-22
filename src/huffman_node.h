#pragma once

#include <memory>
#include "constants.h"

struct HuffmanNode {
    explicit HuffmanNode(bool is_terminal, CharType symbol) : is_terminal(is_terminal), symbol(symbol) {
    }
    HuffmanNode() {
    }
    std::shared_ptr<HuffmanNode> left_child = nullptr;
    std::shared_ptr<HuffmanNode> right_child = nullptr;
    bool is_terminal = false;
    CharType symbol = 0;
};
