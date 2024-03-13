#include "mockos/PermissionProxy.h"

#include <iostream>
#include "mockos/enums.h"

PermissionProxy::PermissionProxy(AbstractFile * f)
:protectedFile(f){}

PermissionProxy::~PermissionProxy() noexcept {
    delete protectedFile;
}

std::vector<char> PermissionProxy::read() {
    return protectedFile->read();
}

int PermissionProxy::write(std::vector<char> input) {
    std::cout << "This is a read_only_file" << std::endl;
    return read_only;
}

int PermissionProxy::append(std::vector<char> input) {
    std::cout << "This is a read_only_file" << std::endl;
    return read_only;
}
unsigned int PermissionProxy::getSize() {
    return protectedFile->getSize();
}
std::string PermissionProxy::getName() {
    return protectedFile->getName();
}

void PermissionProxy::accept(AbstractFileVisitor * afv) {
        protectedFile->accept(afv);
}

AbstractFile * PermissionProxy::clone(std::string newName) {
    AbstractFile * fileClone = this->protectedFile->clone(newName);
    AbstractFile * Clone = new PermissionProxy(fileClone);
    return Clone;
}

AbstractFile * PermissionProxy::getFile() {
    return protectedFile;
}