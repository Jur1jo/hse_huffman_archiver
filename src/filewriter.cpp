#include "filewriter.h"
#include "parserexception.h"
#include <assert.h>

size_t FileWriter::ReverseBit(size_t value) {
    return BIT_LENGTH - 1 - value;
}

void FileWriter::WriteBit(bool value) {
    if (buffer_iterator_ % BIT_LENGTH == 0) {
        buffer_[buffer_iterator_ / BIT_LENGTH] = 0;
    }
    if (value) {
        buffer_[buffer_iterator_ / BIT_LENGTH] = static_cast<char>(buffer_[buffer_iterator_ / BIT_LENGTH] |
                                                                   (1 << ReverseBit(buffer_iterator_ % BIT_LENGTH)));
    }
    ++buffer_iterator_;
    if (buffer_iterator_ == BIT_LENGTH * BUFFER_SIZE) {
        file_.write(buffer_, BUFFER_SIZE);
        buffer_iterator_ = 0;
    }
}

void FileWriter::WriteSymbol(CharType value, size_t length) {
    for (size_t i = length; i > 0; --i) {
        WriteBit(value & (1 << (i - 1)));
    }
}

FileWriter::FileWriter(std::string file_name) {
    file_.open(file_name);
    if (!file_.is_open()) {
        throw ParserException("Can't open archive");
    }
}

FileWriter::~FileWriter() {
    file_.write(buffer_, (static_cast<int32_t>(buffer_iterator_) + BIT_LENGTH - 1) / BIT_LENGTH);
    file_.close();
}