#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "constants.h"

class FileWriter {
public:
    void WriteBit(bool value);
    void WriteSymbol(CharType value, size_t length);
    explicit FileWriter(std::string file_name);
    ~FileWriter();

private:
    size_t ReverseBit(size_t value);
    std::ofstream file_;
    static const size_t BUFFER_SIZE = 8;
    char buffer_[BUFFER_SIZE];
    size_t buffer_iterator_ = 0;
};
