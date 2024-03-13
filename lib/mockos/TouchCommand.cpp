#include "mockos/TouchCommand.h"
#include "mockos/PasswordProxy.h"

TouchCommand::TouchCommand(AbstractFileSystem * sys, AbstractFileFactory *fac)
:system(sys), factory(fac){}

void TouchCommand::displayInfo() {
    std::cout << "Touch creates a file, touch can be invoked with the command 'touch <filename>' or 'touch <filename> -p" << std::endl;
}

int TouchCommand::execute(std::string name) {
    std::istringstream iss(name);
    std::string fileName;
    iss >> fileName;
    if(fileName.size() >= maximum_name_length){
        std::cout << "File name is too long" << std::endl;
        return file_name_too_long;
    }
    AbstractFile * file = factory->createFile(fileName);
    if(file == nullptr){
        std::cout << "Fail to create file" << std::endl;
        return fail_to_create_file;
    }
    if(name.find("-p") != std::string::npos){
        std::string password;
        std::cout << "What is the password?" << std::endl;
std::getline(std::cin, password);
        //check password
        PasswordProxy * proxy = new PasswordProxy(file, password);
        int result = system ->addFile(fileName, proxy);
        if (result != success) {
            delete proxy;
            return result;
        };
    }
    else {
        int result = system->addFile(fileName, file);
        if (result != success) {
            delete file;
            return result;
        };
    }
    return success;
}