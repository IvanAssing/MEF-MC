#ifndef ELEMENT_H
#define ELEMENT_H

#include "node.h"
#include "boundaryintersection.h"
#include "triangleelement.h"

namespace MC
{
    class Element  : public Graphic
    {
        public:
            int index;
            int index1;
            int index2;
            double *edges;
            Element **adjacentElements;
            BoundaryIntersection *intersections;
            int nIntersections;

            TriangleElement *triangles;
            int nTriangles;

            Element();
            Element(int index, int index1, int index2);

            void setEdges(double *edges);
            void draw(void);
            bool findIntersection(BoundaryElement *boundaryElement);
            static int normalizeEdge(int edge);
            void setIntersection(TypeIntersection type, BoundaryIntersection intersection);

            void findTriangleDivision(void);
            void findTriangleDivision_2(void);
            void findTriangleDivision_3(void);
    };
}
#endif // ELEMENT_H
