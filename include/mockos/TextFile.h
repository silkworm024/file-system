#pragma once
#include "AbstractFile.h"
#include <iostream>

class TextFile : public AbstractFile{
public:
    TextFile(std::string);
    TextFile(std::string n, std::vector<char> cont);
    virtual std::vector<char> read();
    virtual int write(std::vector<char>);
    virtual int append(std::vector<char>);
    virtual unsigned int getSize();
    virtual std::string getName();
    virtual void accept(AbstractFileVisitor *);
    virtual AbstractFile * clone(std::string);
private:
    std::string name;
    std::vector<char> content;
};