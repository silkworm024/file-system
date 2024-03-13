#include "mockos/PermissionCommand.h"
#include "mockos/PermissionProxy.h"

PermissionCommand::PermissionCommand(AbstractFileSystem * sys, AbstractFileFactory * fac)
:system(sys), factory(fac){}

void PermissionCommand::displayInfo() {
    std::cout << "Permission command change the permission of a file to read-only or undo the change. To add read-only permission, do 'chmod -r <fileName>'. To remove the permission, do 'chmod -w <fileName>'" << std::endl;
}

int PermissionCommand::execute(std::string input) {
    if(input.find("-r") != std::string::npos || input.find("-w") != std::string::npos) {
        std::istringstream iss(input);
        std::string perm; std::string fileName;
        iss >> perm; iss >> fileName;
        AbstractFile * file = system->openFile(fileName);
        if (file == nullptr){
            std::cout << "Fail to open file" << std::endl;
            return fail_to_open_file;
        }
        if(input.find("-r") != std::string::npos){
            if(dynamic_cast<PermissionProxy *> (file) == nullptr){
                AbstractFile * clone = file->clone(fileName);
                AbstractFile * proxy = new PermissionProxy(clone);
                system->closeFile(file);
                system->deleteFile(fileName);
                system->addFile(fileName, proxy);
            }
            else{
                std::cout << "The file is already read_only" << std::endl;
                system->closeFile(file);
                return already_read_only;
            }
        }
        else {
            if (dynamic_cast<PermissionProxy *> (file) != nullptr) {
                AbstractFile * clone = dynamic_cast<PermissionProxy *> (file)->getFile()->clone(fileName);
                system->closeFile(file);
                system->deleteFile(fileName);
                system->addFile(fileName, clone);
            } else {
                std::cout << "The file doesn't have read_only permission" << std::endl;
                system->closeFile(file);
                return already_no_permission;
            }
        }
    }
else{
    std::cout << "Wrong command format" << std::endl;
    return wrong_format;
}
return success;
}