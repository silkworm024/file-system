#include "mockos/LSCommand.h"
#include "mockos/MetadataDisplayVisitor.h"
#include <sstream>
#include <iomanip>


LSCommand::LSCommand(AbstractFileSystem * sys): system(sys){
}

void LSCommand::displayInfo() {
    std::cout << "List (ls) lists all file names in the system to the user terminal. List can be invoked by typing 'ls' to the console or 'ls -m' to have a mono-list." << std::endl;
}

int LSCommand::execute(std::string name) {
    int listLength;
    if(name.find("-m") != std::string::npos){
        listLength = once;
    } else {
        listLength = twice;
    }

    std::set<std::string> fn = system->getFileNames();

        if (listLength == once){ //display metadata
            MetadataDisplayVisitor bv;
            for(auto it = fn.begin(); it != fn.end(); ++it){
                AbstractFile * file = system ->openFile(*it);
                if(file == nullptr){
                    return fail_to_open_file;
                }
                std::cout << std::setw(maximum_name_length);
                file -> accept(&bv);
                system->closeFile(file);
            }
        }
        else{ //print normal
            int file_on_a_line = 0;
            for(auto it = fn.begin(); it != fn.end(); ++it){
                std::cout << std::setw(maximum_name_length) << *it;
                file_on_a_line++;
                if (file_on_a_line == listLength) {
                    std::cout << std::endl;
                    file_on_a_line = 0;
                }
            }
            std::cout << std::endl;
        }
        return success;
    }
