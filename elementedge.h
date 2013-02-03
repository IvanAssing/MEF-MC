#ifndef ELEMENTEDGE_H
#define ELEMENTEDGE_H

#include "graphic.h"
#include "boundaryelement.h"

namespace MC
{

class ElementEdge : public Graphic
{
    public:
        int indexH1;
        int indexH2;
        int indexV1;
        int indexV2;
        int dir;

        BoundaryElement *element;
        double ksi;

        ElementEdge();
        ElementEdge(int indexH1, int indexH2, int indexV1, int indexV2, BoundaryElement *element, double ksi, int dir);

        void draw(void);
};
}

#endif // ELEMENTEDGE_H
