#include "mockos/MetadataDisplayVisitor.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"

void MetadataDisplayVisitor::visit_TextFile(TextFile * text) {
    std::cout << text->getName() << " text " << text->getSize() << std::endl;
}

void MetadataDisplayVisitor::visit_ImageFile(ImageFile * image) {
    std::cout << image->getName() << " image " << image->getSize() << std::endl;
}