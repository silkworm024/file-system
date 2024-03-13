#include "mockos/EditDisplayParsingStrategy.h"
#include <sstream>
#include <vector>

std::vector<std::string> EditDisplayParsingStrategy::parse(std::string input) {
    std::istringstream iss(input);
    std::string fileName; std::string add_command; std::string add_command_2;
    std::vector<std::string> result;
    iss >> fileName;
if(iss >> add_command) {
    if (add_command != "-a") {
        if (add_command == "-d") {
            add_command_2 = "-d";
        }
        add_command = "";
    }
    if (iss >> add_command_2) {
        if (add_command_2 != "-d") {
            add_command_2 = "";
        }
    }
}
result.push_back(fileName + " " + add_command);
    result.push_back(fileName + " " + add_command_2);
return result;
}

std::string EditDisplayParsingStrategy::get_info() {
    return info;
}

void EditDisplayParsingStrategy::setInfo() {
    info = "EditDisplay command allows you to edit a file and display it immediately. It can be invoked by 'catds'. Additional options: 'catds -a -d' to append and display without format, 'catds -d' to display without format";
}

