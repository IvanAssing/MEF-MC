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
            BoundaryNode **nodes;
            BoundaryElement();
    };
}
#endif // BOUNDARYELEMENT_H
