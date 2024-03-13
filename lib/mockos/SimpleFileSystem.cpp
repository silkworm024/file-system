#include "mockos/SimpleFileSystem.h"
#include "mockos/enums.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"

SimpleFileSystem::~SimpleFileSystem(){
for(auto it = all_files.begin(); it != all_files.end(); ++it){
    delete it->second;
}
}

int SimpleFileSystem::addFile(std::string name, AbstractFile * file) {
    if(all_files.find(name) != all_files.end()){
        std::cout << "File already exist" << std::endl;
        return file_already_exist;
    }
    if(file == nullptr){
        std::cout << "File is null" << std::endl;
        return file_is_null;
    }
    all_files.insert(std::pair<std::string, AbstractFile *>(name, file));
    return success_system;
}

AbstractFile * SimpleFileSystem::openFile(std::string name) {
    if(all_files.find(name) != all_files.end() && open_files.find(all_files[name]) == open_files.end()){
        open_files.insert(all_files[name]);
        return all_files[name];
    }
        return nullptr;
}

int SimpleFileSystem::closeFile(AbstractFile * file) {
    if(open_files.find(file) == open_files.end()){
        std::cout << "File is not open" << std::endl;
        return file_not_open;
    }
    open_files.erase(file);
    return success_system;
}

int SimpleFileSystem::deleteFile(std::string name) {
    if(all_files.find(name) == all_files.end()){
        std::cout << "File doesn't exist" << std::endl;
        return file_not_exist;
    }
    if(open_files.find(all_files[name]) != open_files.end()){
        std::cout << "Can't delete an open file" << std::endl;
        return file_is_open;
    }
    delete all_files[name];
    all_files.erase(name);
    return success_system;
}
std::set<std::string> SimpleFileSystem::getFileNames() {
    std::set<std::string> filenames;
   for( auto it = all_files.begin(); it!=all_files.end(); ++it){
       filenames.insert(it->first);
   }
   return filenames;
}