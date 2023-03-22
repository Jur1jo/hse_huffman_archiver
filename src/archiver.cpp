#include "archivator.h"
#include "unarchivator.h"
#include "parserexception.h"
#include "myparser.h"
#include <iostream>

int main(int argc, char** argv) {
    MyParser parser(argc, argv);
    parser.AddParameter(
        "The -c command is used for archiving:\nWrite the name of the result archive, and then the archived files");
    parser.AddParameter("The -d command is used for unarchiving:\nWrite the name of the archive");
    if (parser.HasArgument('h')) {
        parser.PrintHelp(std::cout);
    }
    if (parser.HasArgument('c')) {
        auto list_files = parser.GetArgument('c');
        if (list_files.size() == 1) {
            throw ParserException("List of archived name shouldn't empty");
        }
        Archivator archiver;
        std::vector<std::string> archived_files;
        for (size_t i = 1; i < list_files.size(); ++i) {
            archived_files.push_back(list_files[i]);
        }
        archiver.ArchiveFile(archived_files, list_files[0]);
    }
    if (parser.HasArgument('d')) {
        auto list_files = parser.GetArgument('d');
        if (list_files.size() != 1) {
            throw ParserException("You should give only once name of the unarchiving files");
        }
        Unarchivator archiver;
        archiver.UnarchiveFile(list_files[0]);
    }
    return 0;
}
