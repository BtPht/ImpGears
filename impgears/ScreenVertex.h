#ifndef IMP_SCREENVERTEX_H
#define IMP_SCREENVERTEX_H

#include "base/impBase.hpp"
#include "graphics/VBOData.h"
#include "scene/SceneNode.h"

IMPGEARS_BEGIN

class ScreenVertex : public VBOData, public SceneNode
{
    public:
        ScreenVertex();
        virtual ~ScreenVertex();

        virtual void render(imp::Uint32 passID);

    protected:
    private:

        Uint64 m_texCoordOffset;
};

IMPGEARS_END

#endif // IMP_SCREENVERTEX_H
