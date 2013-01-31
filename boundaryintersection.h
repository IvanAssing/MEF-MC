#ifndef BOUNDARYINTERSECTION_H
#define BOUNDARYINTERSECTION_H

#include "boundaryelement.h"
#include "polynomial1d.h"
#include "graphic.h"

namespace MC
{
    enum TypeIntersection{
        Input,
        Output
    };

    class BoundaryIntersection : public Graphic
    {
        public:
            BoundaryElement *element;
            double ksi;
            int edge;

            BoundaryIntersection();
            BoundaryIntersection(BoundaryElement *element, double ksi, int edge);

            void draw(void);
    };
}

#endif // BOUNDARYINTERSECTION_H
