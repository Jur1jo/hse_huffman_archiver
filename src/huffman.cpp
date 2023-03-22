#include "huffman.h"
#include "queuenode.h"
#include "parserexception.h"
#include <algorithm>

QueueMin<QueueNode> HuffmanCode::BuildQueue(std::unordered_map<CharType, size_t> number_entry) {
    std::vector<QueueNode> node_number_entry;
    for (const auto &i : number_entry) {
        node_number_entry.emplace_back(i.second, i.first, 1);
    }
    return QueueMin<QueueNode>(node_number_entry);
}

HuffmanCode::HuffmanCode(std::unordered_map<CharType, size_t> number_entry) {
    QueueMin min_number_entry = BuildQueue(number_entry);
    while (min_number_entry.Size() > 1) {
        auto v1 = min_number_entry.GetMinValue();
        auto v2 = min_number_entry.GetMinValue();
        std::shared_ptr<HuffmanNode> new_node = std::make_shared<HuffmanNode>(false, 0);
        new_node->left_child = v1.GetNode();
        new_node->right_child = v2.GetNode();
        min_number_entry.AddValue(
            QueueNode(v1.GetNumberEntry() + v2.GetNumberEntry(), std::min(v1.GetSymbol(), v2.GetSymbol()), new_node));
    }
    std::vector<std::pair<CharType, CharType>> old_code;
    DfsHuffman(min_number_entry.GetMinValue().GetNode(), old_code, 0);
    std::sort(old_code.begin(), old_code.end());
    ToCanonical(old_code);
}

HuffmanCode::HuffmanCode(std::vector<std::pair<CharType, CharType>> old_code) {
    ToCanonical(old_code);
}

void HuffmanCode::DfsHuffman(std::shared_ptr<HuffmanNode> v, std::vector<std::pair<CharType, CharType>> &old_code,
                             size_t cur_length) {
    if (v->is_terminal) {
        old_code.emplace_back(cur_length, v->symbol);
        return;
    }

    if (v->right_child != nullptr) {
        DfsHuffman(v->right_child, old_code, cur_length + 1);
    }
    if (v->left_child != nullptr) {
        DfsHuffman(v->left_child, old_code, cur_length + 1);
    }
}

void HuffmanCode::ToCanonical(const std::vector<std::pair<CharType, CharType>> &old_code) {  // length, symbol
    std::vector<bool> current_code;
    while (current_code.size() < old_code[0].first) {
        current_code.push_back(false);
    }
    normalize_tree_ = current_node_ = std::make_shared<HuffmanNode>(false, 0);
    for (const auto &i : old_code) {
        if (i != old_code[0]) {
            while (current_code.back()) {
                current_code.pop_back();
            }
            current_code.pop_back();
            current_code.push_back(true);
            while (current_code.size() < i.first) {
                current_code.push_back(false);
            }
        }
        while (number_length_huffman_code.size() < i.first) {
            number_length_huffman_code.push_back(0);
        }
        ++number_length_huffman_code[i.first - 1];
        list_symbols.push_back(i.second);
        canonical_code_[i.second] = current_code;
        for (auto current_bit : current_code) {
            if (current_bit) {
                if (current_node_->right_child == nullptr) {
                    current_node_->right_child = std::make_shared<HuffmanNode>(false, 0);
                }
                current_node_ = current_node_->right_child;
            } else {
                if (current_node_->left_child == nullptr) {
                    current_node_->left_child = std::make_shared<HuffmanNode>(false, 0);
                }
                current_node_ = current_node_->left_child;
            }
        }
        current_node_->is_terminal = true;
        current_node_->symbol = i.second;
        current_node_ = normalize_tree_;
    }
}
const CharType HuffmanCode::ReadBit(bool value) {
    if (value == 1) {
        if (current_node_->right_child == nullptr) {
            throw ParserException("Incorrect archive");
        }
        current_node_ = current_node_->right_child;
    } else {
        if (current_node_->left_child == nullptr) {
            throw ParserException("Incorrect archive");
        }
        current_node_ = current_node_->left_child;
    }
    if (current_node_->is_terminal) {
        auto result = current_node_->symbol;
        current_node_ = normalize_tree_;
        return result;
    } else {
        return NON_TERMINAL;
    }
}

void HuffmanCode::PrintSymbol(CharType symbol, FileWriter &writer) {
    for (auto i : canonical_code_[symbol]) {
        writer.WriteBit(i);
    }
}
