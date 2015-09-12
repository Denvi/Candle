#ifndef ORIGINDRAWER_H
#define ORIGINDRAWER_H

#include "shaderdrawable.h"

class OriginDrawer : public ShaderDrawable
{
public:
    OriginDrawer();

protected:
    bool updateData();
};

#endif // ORIGINDRAWER_H
