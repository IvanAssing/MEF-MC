#ifndef BOUNDARYINTERSECTION_H
#define BOUNDARYINTERSECTION_H

#include "boundaryelement.h"
#include "polynomial1d.h"

namespace MC
{
    class BoundaryIntersection
    {
        public:
            BoundaryElement *element;
            double ksi;
            int edge;

            BoundaryIntersection();
            BoundaryIntersection(BoundaryElement *element, double ksi, int edge);
    };
}

#endif // BOUNDARYINTERSECTION_H
