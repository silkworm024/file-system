#include "mockos/ImageFile.h"
#include "mockos/enums.h"
#include "mockos/AbstractFileVisitor.h"

ImageFile::ImageFile(std::string name)
:name(name), size(none){}

std::string ImageFile::getName() {
    return name;
}

unsigned int ImageFile::getSize() {
    return contents.size();
}

int ImageFile::write(std::vector<char> input) {
    size = input[input.size() - 1] - converter;
    if(input.size() - 1 == size * size) {
        for(unsigned int i = 0; i < input.size() - 1; ++i) {
            if(input[i] == 'X' || input[i] == ' ') {
                contents.push_back(input[i]);
            }
            else{
                size = 0;
                contents.clear();
                std::cout << "Input is invalid" << std::endl;
                return invalid_input;
            }
        }
    }
    else{
        size = 0;
        contents.clear();
        std::cout << "Wrong input size" << std::endl;
        return wrong_size;
    }
    return success;
}

int ImageFile::append(std::vector<char>) {
    std::cout << "Append is not supported for image file" << std::endl;
    return function_not_supported;
}

std::vector<char> ImageFile::read(){
    return contents;
}

void ImageFile::accept(AbstractFileVisitor * visitor){
    visitor->visit_ImageFile(this);
}

ImageFile::ImageFile(std::string n, std::vector<char> cont, char sz) : name(n), contents(cont),size(sz) {
}

AbstractFile * ImageFile::clone(std::string newName) {
    //extension can also be added here
    AbstractFile * clone = new ImageFile(newName,this->contents,this->size);
    return clone;
}