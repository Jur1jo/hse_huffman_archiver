#include "filereader.h"
#include "parserexception.h"
#include <iostream>

size_t FileReader::ReverseBit(size_t value) {
    return BIT_LENGTH - 1 - value;
}

const bool FileReader::GetBit() {
    if (buffer_iterator_ == BUFFER_SIZE * BIT_LENGTH) {
        file_.read(buffer_, BUFFER_SIZE);
        max_value_iterator_ = file_.gcount() * BIT_LENGTH;
        buffer_iterator_ = 0;
    }
    if (buffer_iterator_ > max_value_iterator_) {
        throw ParserException("Incorrect archive");
    }
    bool result = buffer_[buffer_iterator_ / BIT_LENGTH] & (1 << ReverseBit(buffer_iterator_ % BIT_LENGTH));
    ++buffer_iterator_;
    return result;
}

CharType FileReader::ReadChar(size_t number_bits) {
    CharType result = 0;
    for (size_t j = number_bits; j > 0; --j) {
        if (GetBit()) {
            result += (1 << (j - 1));
        }
    }
    return result;
}

FileReader::FileReader(std::string file_name) : file_name_(file_name) {
    file_.open(file_name, std::ios::in | std::ios::binary);
    if (!file_.is_open()) {
        throw ParserException("Can't open archive");
    }
}

void FileReader::ClearBuffer() {
    file_.close();
    file_.open(file_name_, std::ios::in | std::ios::binary);
    if (!file_.is_open()) {
        throw ParserException("Can't open archive");
    }
    buffer_iterator_ = BUFFER_SIZE * BIT_LENGTH;
    max_value_iterator_ = 0;
}

FileReader::~FileReader() {
    file_.close();
}

const bool FileReader::Empty() {
    if (buffer_iterator_ == BUFFER_SIZE * BIT_LENGTH) {
        file_.read(buffer_, BUFFER_SIZE);
        max_value_iterator_ = file_.gcount() * BIT_LENGTH;
        buffer_iterator_ = 0;
    }
    return buffer_iterator_ == max_value_iterator_;
}