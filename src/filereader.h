#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "constants.h"

class FileReader {
public:
    const bool GetBit();
    CharType ReadChar(size_t number_bits);
    explicit FileReader(std::string file_name);
    const bool Empty();
    ~FileReader();
    void ClearBuffer();

private:
    size_t ReverseBit(size_t value);
    std::ifstream file_;
    static const size_t BUFFER_SIZE = 1;
    char buffer_[BUFFER_SIZE];
    size_t buffer_iterator_ = BUFFER_SIZE * 8;
    size_t max_value_iterator_ = 0;
    std::string file_name_;
};