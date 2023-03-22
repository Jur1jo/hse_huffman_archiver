#pragma once

#include <unordered_map>
#include <vector>
#include "huffman_node.h"
#include "constants.h"
#include "filewriter.h"
#include "queue_min.h"
#include "queuenode.h"

class HuffmanCode {
public:
    explicit HuffmanCode(std::unordered_map<CharType, size_t> number_entry);
    explicit HuffmanCode(std::vector<std::pair<CharType, CharType>> old_code);  // length, symbol
    const CharType ReadBit(bool value);
    void PrintSymbol(CharType symbol, FileWriter& writer);
    std::vector<CharType> list_symbols;
    std::vector<CharType> number_length_huffman_code;

private:
    void DfsHuffman(std::shared_ptr<HuffmanNode> v, std::vector<std::pair<CharType, CharType>>& old_code,
                    size_t cur_length);
    void ToCanonical(const std::vector<std::pair<CharType, CharType>>& old_code);  // Length, Symbol
    QueueMin<QueueNode> BuildQueue(std::unordered_map<CharType, size_t> number_entry);
    std::shared_ptr<HuffmanNode> normalize_tree_ = nullptr;
    std::shared_ptr<HuffmanNode> current_node_ = nullptr;
    std::unordered_map<CharType, std::vector<bool>> canonical_code_;
};
