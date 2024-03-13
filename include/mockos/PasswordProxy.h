#pragma once
#include <iostream>
#include <string>
#include "AbstractFile.h"

class PasswordProxy: public AbstractFile {
public:
    PasswordProxy(AbstractFile*,std::string);
    virtual AbstractFile* clone(std::string);
    ~PasswordProxy() noexcept;
    virtual std::vector<char> read();
    virtual int write(std::vector<char>);
    virtual int append(std::vector<char>);
    virtual std::string getName();
    virtual unsigned int getSize();
    virtual void accept(AbstractFileVisitor *);
    int doTheyMatch(std::string);
protected:
    std::string passwordPrompt();
private:
    AbstractFile * protectedFile;
    std::string password;

};