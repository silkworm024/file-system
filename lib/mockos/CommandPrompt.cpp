#include "mockos/CommandPrompt.h"
#include <iomanip>

CommandPrompt::CommandPrompt()
:system(nullptr), factory(nullptr){}

void CommandPrompt::setFileSystem(AbstractFileSystem * sys) {
    system = sys;
}

void CommandPrompt::setFileFactory(AbstractFileFactory * fac) {
    factory = fac;
}

int CommandPrompt::addCommand(std::string name, AbstractCommand * command) {
    if (commands.find(name) != commands.end()) {
        std::cout << "Command already exists" << std::endl;
        return command_already_exist;
    }
    commands.insert(std::pair<std::string, AbstractCommand *>(name, command));
    return success;
}

void CommandPrompt::listCommands() {
    for(auto it = commands.cbegin(); it != commands.cend(); ++it){
        std::cout << it->first << std::endl;
    }
}

std::string CommandPrompt::prompt() {
    std::cout << "Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command." << std::endl;
    std::cout << std::setw(command_spacing) << "$  ";
    std::string command;
    std::getline(std::cin, command);
  return command;
}

int CommandPrompt::run() {
    while(1){
        std::string command = prompt();
        if(command == "q"){
            return quit;
        }
        else if(command == "help"){
            listCommands();
        }
        else{
            //input has more than one words
            if(command.find(' ') != std::string::npos){
std::istringstream iss(command);
std::string first; iss >> first;
if(first == "help"){
    std::string second; iss >> second;
    if(commands.find(second) != commands.end()){
        commands[second]->displayInfo();
    }
    else{
        std::cout << "Command doesn't exist" << std::endl;
        return command_not_exist;
    }
}
else{
    std::string second;
    std::getline(iss, second);
    if(commands.find(first) != commands.end()){
        int result = commands[first]->execute(second);
        if(result != success){
            std::cout << "An error occurs" << std::endl;
            return result;
        }
    }
    else{
        std::cout << "Command doesn't exist" << std::endl;
        return command_not_exist;
    }
    }
            }
                //input has only one word
            else{
                if(commands.find(command) != commands.end()){
                    int result = commands[command]->execute("");
                    if(result != success){
                        std::cout << "An error occurs" << std::endl;
                        return result;
                    }
                }
                else{
                    std::cout << "Command doesn't exist" << std::endl;
                    return command_not_exist;
                }
            }
        }
    }
}