#include "mockos/BasicDisplayVisitor.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include <cmath>
//is this right?

void BasicDisplayVisitor::visit_TextFile(TextFile * text){
    for (unsigned int i = 0;i < text->read().size();i++){
        std::cout << text->read()[i];
    }
    std::cout << std::endl;
}

void BasicDisplayVisitor::visit_ImageFile(ImageFile * image) {
    int size = sqrt(image->getSize());
    for(int i = size - 1; i >= 0; --i){
        for(int j = 0; j < size; ++j){
           std::cout << image->read()[size * i + j];
        }
       std::cout << std::endl;
    }
}