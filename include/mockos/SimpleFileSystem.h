#pragma once
#include "AbstractFileSystem.h"

class SimpleFileSystem : public AbstractFileSystem{
public:
    virtual int addFile(std::string, AbstractFile *);
    virtual int deleteFile(std::string);
    virtual AbstractFile * openFile(std::string);
    virtual int closeFile(AbstractFile *);
    virtual std::set<std::string> getFileNames();
    ~SimpleFileSystem();
private:
    std::map<std::string, AbstractFile *> all_files;
    std::set<AbstractFile *> open_files;
};