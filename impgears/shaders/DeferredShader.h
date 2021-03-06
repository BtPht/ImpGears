#ifndef IMP_DEFERREDSHADER_H
#define IMP_DEFERREDSHADER_H

#include "base/impBase.hpp"
#include "shaders/Shader.h"

IMPGEARS_BEGIN

class DeferredShader : public Shader
{
    public:
        DeferredShader();
        virtual ~DeferredShader();

        static DeferredShader* instance;

    protected:
    private:

        static const char* vertexCodeSource;
        static const char* fragmentCodeSource;
};

IMPGEARS_END

#endif // IMP_DEFERREDSHADER_H
