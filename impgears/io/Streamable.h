/*
io/IGStreamable.h

Define an interface for reading or writing a object from or to a file.
*/

#ifndef IMP_STREAMABLE_H
#define IMP_STREAMABLE_H

#include "io/Parser.h"

IMPGEARS_BEGIN

class Streamable
{
public:
    Streamable();
    virtual ~Streamable();

    virtual void Load(Parser* _parser) = 0;
    virtual void Save(Parser* _parser) = 0;
};

IMPGEARS_END

#endif // IMP_STREAMABLE_H
