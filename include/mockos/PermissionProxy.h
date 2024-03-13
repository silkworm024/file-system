#pragma once
#include "AbstractFile.h"

class PermissionProxy: public AbstractFile {
public:
    PermissionProxy(AbstractFile *);
    virtual AbstractFile* clone(std::string);
    ~PermissionProxy() noexcept;
    virtual std::vector<char> read();
    virtual int write(std::vector<char>);
    virtual int append(std::vector<char>);
    virtual std::string getName();
    virtual unsigned int getSize();
    virtual void accept(AbstractFileVisitor *);
    AbstractFile * getFile();
private:
    AbstractFile * protectedFile;
};