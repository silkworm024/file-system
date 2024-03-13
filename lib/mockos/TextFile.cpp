#include "mockos/TextFile.h"
#include "mockos/enums.h"
#include "mockos/AbstractFileVisitor.h"

TextFile::TextFile(std::string s)
:name(s){}

unsigned int TextFile::getSize() {
    return content.size();
}

std::string TextFile::getName() {
    return name;
}

int TextFile::write(std::vector<char> input) {
    content = input;
    return success;
    }

int TextFile::append(std::vector<char> added) {
    for (int i = 0; i < added.size(); i++){
        content.push_back(added[i]);
    }
    //another way: std::copy(added.cbegin(), added.cend(), std::back_inserter(content));
    return success;
}

std::vector<char> TextFile::read() {
    return content;
}

void TextFile::accept(AbstractFileVisitor * visitor){
    visitor->visit_TextFile(this);
}

TextFile::TextFile(std::string n, std::vector<char> cont) : name(n), content(cont) {
}

AbstractFile *TextFile::clone(std::string newName) {
    AbstractFile * clone = new TextFile(newName,this->content);
    return clone;
}