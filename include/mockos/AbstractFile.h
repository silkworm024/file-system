#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

class AbstractFileVisitor; //forward declaration

class AbstractFile{
public:
    virtual std::vector<char> read() = 0;
    virtual int write(std::vector<char>) = 0;
    virtual int append(std::vector<char>) = 0;
    virtual unsigned int getSize() = 0;
    virtual std::string getName() = 0;
    virtual void accept(AbstractFileVisitor *) = 0;
    virtual ~AbstractFile() = default;
    virtual AbstractFile* clone(std::string) = 0;
};
