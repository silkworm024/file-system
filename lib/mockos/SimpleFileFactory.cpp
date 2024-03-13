#include <algorithm>
#include "mockos/SimpleFileFactory.h"
#include "mockos/enums.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"

AbstractFile * SimpleFileFactory::createFile(std::string name) {
    std::string extension; bool is_extension = true;
    for(int i = name.size() - 1; i >= 0; --i){
        if(name[i] == '.'){
            is_extension = false;
        }
        if(is_extension){
            extension += name[i];
        }
    }
    std::reverse(extension.begin(), extension.end());
    if(extension == "txt"){
        AbstractFile * file = new TextFile(name);
        return file;
    }
    if(extension == "img"){
        AbstractFile * file = new ImageFile(name);
        return file;
    }
    return nullptr; // file type is not recognised!
}

