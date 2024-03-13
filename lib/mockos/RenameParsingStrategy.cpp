#include "mockos/RenameParsingStrategy.h"

std::vector<std::string> RenameParsingStrategy::parse(std::string input) {
std::string file;
std::istringstream iss(input);
iss >> file;
std::vector<std::string> result;
result.push_back(input); result.push_back(file);
return result;
}

std::string RenameParsingStrategy::get_info() {
    return info;
}

void RenameParsingStrategy::setInfo() {
    info = "Rename command renames a file. Rename command can be invoked by 'rn <existing_file> <new_name_with_no_extension>'";
}