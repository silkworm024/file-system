#include "mockos/RemoveCommand.h"

RemoveCommand::RemoveCommand(AbstractFileSystem * sys) : system(sys){

}

void RemoveCommand::displayInfo() {
    std::cout << "Remove deletes a file, remove can be invoked with the command 'rm <filename>'" << std::endl;
}

int RemoveCommand::execute(std::string name) {
    std::istringstream iss(name);
    std::string fileName;
    iss >> fileName;
    int result = system->deleteFile(fileName);

    return result;

}