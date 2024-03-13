#pragma once
#include "AbstractFileVisitor.h"

class BasicDisplayVisitor : public AbstractFileVisitor{
public:
    virtual void visit_TextFile(TextFile *);
    virtual void visit_ImageFile(ImageFile *);
};