#ifndef ELEMENT_H
#define ELEMENT_H

#include "node.h"
#include "boundaryintersection.h"

namespace MC
{
    class Element  : public Graphic
    {
        public:
            int index;
            double *edges;
            Element **adjacentElements;
            BoundaryIntersection *intersections;

            Element();
            Element(int index);

            void setEdges(double *edges);
            void draw(void);
    };
}
#endif // ELEMENT_H
