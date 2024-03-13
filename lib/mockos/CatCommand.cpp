#include "mockos/CatCommand.h"

CatCommand::CatCommand(AbstractFileSystem * sys)
:system(sys){}

void CatCommand::displayInfo() {
    std::cout << "Cat concatenates files, cat can be invoked with the command 'cat <filename>' or 'cat <filename> -a" << std::endl;
}

int CatCommand::execute(std::string name) {
    std::istringstream iss(name);
    std::string fileName;
    iss >> fileName;
    AbstractFile * file = system->openFile(fileName);
    if(file == nullptr){
        std::cout << "Fail to open file" << std::endl;
        return fail_to_open_file;
    }
    int result = success;
    if(name.find("-a") != std::string::npos) {
std::ostream_iterator<char> out_it(std::cout);
std::vector<char> content = file->read();
std::copy(content.cbegin(), content.cend(), out_it);
std::cout << std::endl;
std::cout << "Enter the data you would like to append to the file" << std::endl;
std::string input; std::vector<char> all_input;
std::getline(std::cin, input);
bool first = true;
while(input != ":wq" && input != ":q"){
    if(!first) {
        all_input.push_back('\n');
    }
        copy(input.cbegin(), input.cend(), back_inserter(all_input));
        std::getline(std::cin, input);
        first = false;
}
if(input == ":wq"){
    result = file->append(all_input);
}
    }
    else{
        std::cout << "Enter the data you would like to write to the file" << std::endl;
        std::string input; std::vector<char> all_input;
        std::getline(std::cin, input);
        bool first = true;
        while(input != ":wq" && input != ":q"){
            if(!first) {
                all_input.push_back('\n');
            }
            copy(input.cbegin(), input.cend(), back_inserter(all_input));
            std::getline(std::cin, input);
            first = false;
        }
        if(input == ":wq"){
            result = file->write(all_input);
        }
    }
    system->closeFile(file);
    return result;
}