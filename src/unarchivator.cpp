#include "unarchivator.h"
#include "parserexception.h"

CharType Unarchivator::ReadOnceSymbol(FileReader& reader, HuffmanCode& huffman_code) {
    while (true) {
        CharType current_symbol = huffman_code.ReadBit(reader.GetBit());
        if (current_symbol != NON_TERMINAL) {
            return current_symbol;
        }
    }
}

HuffmanCode Unarchivator::ReadSymbols(FileReader& reader) {
    CharType number_symbol = reader.ReadChar(CHAR_LENGTH + 1);
    std::vector<CharType> list_symbols(number_symbol);
    for (auto& i : list_symbols) {
        i = reader.ReadChar(CHAR_LENGTH + 1);
    }
    std::vector<CharType> number_length;
    size_t summary_symbols = 0;
    while (summary_symbols < list_symbols.size()) {
        CharType current_number = reader.ReadChar(CHAR_LENGTH + 1);
        summary_symbols += current_number;
        number_length.emplace_back(current_number);
    }
    if (summary_symbols != list_symbols.size()) {
        throw ParserException("Incorrect Archive");
    }
    std::vector<std::pair<CharType, CharType>> symbol_code_length;  // length, symbol
    size_t iterator_code_length = 0;
    for (const auto& i : list_symbols) {
        while (iterator_code_length < number_length.size() && !number_length[iterator_code_length]) {
            ++iterator_code_length;
        }

        symbol_code_length.emplace_back(iterator_code_length + 1, i);
        --number_length[iterator_code_length];
    }
    return HuffmanCode(symbol_code_length);
}

bool Unarchivator::UnarchiveOnceFile(FileReader& reader) {
    auto huffman_code = ReadSymbols(reader);
    std::string result_file_name;
    while (true) {
        CharType current_symbol = ReadOnceSymbol(reader, huffman_code);
        if (current_symbol == FILENAME_END) {
            break;
        } else {
            result_file_name += static_cast<char>(current_symbol);
        }
    }
    FileWriter writer(result_file_name);
    while (true) {
        CharType current_symbol = ReadOnceSymbol(reader, huffman_code);
        if (current_symbol == ONE_MORE_FILE) {
            return true;
        } else if (current_symbol == ARCHIVE_END) {
            return false;
        } else {
            writer.WriteSymbol(current_symbol, CHAR_LENGTH);
        }
    }
}

void Unarchivator::UnarchiveFile(std::string file_name) {
    FileReader current_file(file_name);
    while (UnarchiveOnceFile(current_file)) {
    }
}
