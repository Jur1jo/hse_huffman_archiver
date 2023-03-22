#pragma once

#include "huffman.h"
#include "filereader.h"
#include <iostream>

class Unarchivator {
public:
    Unarchivator() {
    }
    void UnarchiveFile(std::string file_name);

private:
    HuffmanCode ReadSymbols(FileReader& reader);
    bool UnarchiveOnceFile(FileReader& reader);
    CharType ReadOnceSymbol(FileReader& reader, HuffmanCode& huffman_code);
};
