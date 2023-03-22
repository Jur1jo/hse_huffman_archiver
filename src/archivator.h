#pragma once

#include "constants.h"
#include "filewriter.h"
#include "huffman.h"
#include "filereader.h"
#include <string>
#include <vector>

class Archivator {
public:
    Archivator() {
    }
    void ArchiveFile(std::vector<std::string> list_file_name, std::string name_file_result);

private:
    std::unordered_map<CharType, size_t> ReadNumberEntry(FileReader& reader, std::string file_name);
    std::string WithoutSlash(std::string s);
    void ArchiveOnceFile(std::string file_name, FileWriter& writer, bool last_file);
};
