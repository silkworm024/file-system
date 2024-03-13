#include "mockos/DisplayCommand.h"
#include "mockos/BasicDisplayVisitor.h"

DisplayCommand::DisplayCommand(AbstractFileSystem * sys) : system(sys){
}

void DisplayCommand::displayInfo() {
    std::cout << "Display displays a file, display can be invoked with the command 'ds <filename>' or 'ds <filename> -d for non-formatted" << std::endl;
}

int DisplayCommand::execute(std::string name) {
    std::istringstream iss(name);
    std::string fileName;
    iss >> fileName;

    AbstractFile * file = system->openFile(fileName);
    if (file != nullptr){
        if (name.find("-d") != std::string::npos){
            std::vector<char> content = file->read();
            for (unsigned int i = 0;i < content.size();i++){
                    std::cout << content[i];
            }
            std::cout << std::endl;
            system->closeFile(file);
            return success;
        } else {
            AbstractFileVisitor * bv = new BasicDisplayVisitor;
            file->accept(bv);
            system->closeFile(file);
            delete bv;
            return success;
        }
    }
    else {
        std::cout << "Fail to open file" << std::endl;
        return fail_to_open_file;
    }
}