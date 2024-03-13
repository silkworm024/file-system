#include "mockos/CopyCommand.h"
#include "mockos/AbstractFile.h"

CopyCommand::CopyCommand(AbstractFileSystem *sys) : system(sys){
}

void CopyCommand::displayInfo() {
    std::cout << "Copy creates a copy of a file, copy can be invoked with the command 'cp <file_to_copy> <new_name_with_no_extension>'"<< std::endl;
    std::cout << "Example: 'cp samplefile.txt samplecopy'" << std::endl;
}

int CopyCommand::execute(std::string name) {

    int result = file_not_exist;

    std::istringstream iss(name);
    std::string fileName;
    std::string fileCopy;
    iss >> fileName;
    iss >> fileCopy;
    AbstractFile * source = system->openFile(fileName);
    AbstractFile * cpy;

    if (fileCopy.empty()){
        std::cout<< "Copy failed. Copy being deleted." << std::endl;
        system->closeFile(source);
        return result;
    }

    if (source == nullptr){
        std::cout << "Fail to open file" << std::endl;
      return fail_to_open_file;
    } else {
        if (fileName.find(".txt") != std::string::npos){
            fileCopy = fileCopy + ".txt";
            cpy = source->clone(fileCopy);
            result = system->addFile(fileCopy,cpy);
        } else if (fileName.find(".img") != std::string::npos){
            fileCopy = fileCopy + ".img";
            cpy = source->clone(fileCopy);
            result = system->addFile(fileCopy,cpy);
        }
    }
    system->closeFile(source);
    if (result == success_system){
        return success;
    }
    else{
        std::cout<< "Copy failed. Copy being deleted." << std::endl;
        delete cpy;
        return result;
    }
}