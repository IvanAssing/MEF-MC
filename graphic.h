#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <GL/gl.h>


namespace MC
{
class Graphic
{
    public:
        Graphic();
        virtual void draw(void) = 0;
};
}

#endif // GRAPHIC_H
