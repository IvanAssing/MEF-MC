#ifndef BOUNDARYELEMENT_H
#define BOUNDARYELEMENT_H

#include "boundarynode.h"
#include "polynomial1d.h"

#define N_NODES_BOUNDARY_ELEMENT 3

namespace MC
{
    class BoundaryElement
    {
        public:
            int index;

            Polynomial1D curveX;
            Polynomial1D curveY;
            BoundaryNode **nodes;

            BoundaryElement();
            BoundaryElement(BoundaryNode *node1, BoundaryNode *node2, BoundaryNode *node3);

            void draw(void);
    };
}
#endif // BOUNDARYELEMENT_H
