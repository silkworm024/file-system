#include "mockos/PasswordProxy.h"
#include "mockos/enums.h"
#include <string>

PasswordProxy::PasswordProxy(AbstractFile * f, std::string pass) : protectedFile(f),password(pass) {

}

PasswordProxy::~PasswordProxy() noexcept {
    delete protectedFile;
}

std::string PasswordProxy::passwordPrompt() {
    std::string userEntry;
    std::cout << "Please enter the file's password." << std::endl;
    std::getline(std::cin, userEntry);

    return userEntry;
}

int PasswordProxy::doTheyMatch(std::string input) {
    bool match;
    if (password.size()==input.size()){
        match = (password==input);
        if (match){
            return success;
        } else {
            return do_not_match;
        }
    } else {
        return wrong_size;
    }
}

std::vector<char> PasswordProxy::read() {
    std::vector<char> contents;
    std::string attemptPass = passwordPrompt();
    int result = doTheyMatch(attemptPass);
    if (result==success){
        contents = protectedFile->read();
        return contents;
    } else {
        std::cout << "Error. Password does not match.";
        return contents;
    }
}

int PasswordProxy::write(std::vector<char> input) {
    std::string attemptPass = passwordPrompt();
    int result = doTheyMatch(attemptPass);
    if (result==success){
        return protectedFile->write(input);
    }else{
        std::cout << "Error. Password does not match.";
        return do_not_match_write;
    }
}

int PasswordProxy::append(std::vector<char> input) {
    std::string attemptPass = passwordPrompt();
    int result = doTheyMatch(attemptPass);
    if (result==success){
        return protectedFile->append(input);
    }else{
        std::cout << "Error. Password does not match.";
        return do_not_match_append;
    }
}
unsigned int PasswordProxy::getSize() {
    return protectedFile->getSize();
}
std::string PasswordProxy::getName() {
    return protectedFile->getName();
}

void PasswordProxy::accept(AbstractFileVisitor * afv) {
    std::string attemptPass = passwordPrompt();
    int result = doTheyMatch(attemptPass);
    if (result==success){
        protectedFile->accept(afv);
    } else {
        std::cout << "Error. Password does not match.";
    }
}

AbstractFile *PasswordProxy::clone(std::string newName) {
    AbstractFile* fileClone = this->protectedFile->clone(newName);// make sure to create new file
    AbstractFile * Clone = new PasswordProxy(fileClone,this->password);
    return Clone;
}