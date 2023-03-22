#include "huffman.h"
#include "archivator.h"
#include "filereader.h"
#include <iostream>

void Archivator::ArchiveFile(std::vector<std::string> list_file_name, std::string name_file_result) {
    FileWriter result_archive(name_file_result);
    for (size_t i = 0; i + 1 < list_file_name.size(); ++i) {
        ArchiveOnceFile(list_file_name[i], result_archive, false);
    }
    ArchiveOnceFile(list_file_name.back(), result_archive, true);
}

std::unordered_map<CharType, size_t> Archivator::ReadNumberEntry(FileReader& reader, std::string file_name) {
    std::unordered_map<CharType, size_t> number_entry;
    while (!reader.Empty()) {
        auto symbol = reader.ReadChar(CHAR_LENGTH);
        number_entry[symbol]++;
    }
    for (const auto& c : file_name) {
        number_entry[c]++;
    }
    number_entry[FILENAME_END] = 1;
    number_entry[ARCHIVE_END] = 1;
    number_entry[ONE_MORE_FILE] = 1;
    reader.ClearBuffer();
    return number_entry;
}

std::string Archivator::WithoutSlash(std::string s) {
    std::string result;
    for (const auto& i : s) {
        if (i == '/') {
            result.clear();
        } else {
            result.push_back(i);
        }
    }
    return result;
}

void Archivator::ArchiveOnceFile(std::string file_name, FileWriter& writer, bool last_file) {
    FileReader reader(file_name);
    auto huffman_code = HuffmanCode(ReadNumberEntry(reader, WithoutSlash(file_name)));
    writer.WriteSymbol(static_cast<CharType>(huffman_code.list_symbols.size()), CHAR_LENGTH + 1);
    for (const auto& i : huffman_code.list_symbols) {
        writer.WriteSymbol(i, CHAR_LENGTH + 1);
    }
    for (const auto& i : huffman_code.number_length_huffman_code) {
        writer.WriteSymbol(i, CHAR_LENGTH + 1);
    }
    for (auto c : WithoutSlash(file_name)) {
        huffman_code.PrintSymbol(c, writer);
    }
    huffman_code.PrintSymbol(FILENAME_END, writer);
    while (!reader.Empty()) {
        auto symbol = reader.ReadChar(CHAR_LENGTH);
        huffman_code.PrintSymbol(symbol, writer);
    }
    if (last_file) {
        huffman_code.PrintSymbol(ARCHIVE_END, writer);
    } else {
        huffman_code.PrintSymbol(ONE_MORE_FILE, writer);
    }
}
