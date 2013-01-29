#ifndef MESH_H
#define MESH_H

#include "node.h"
#include "boundarynode.h"
#include "element.h"
#include "boundaryelement.h"


namespace MC
{
    class Mesh : public Graphic
    {
        public:
            double origin1;
            double origin2;
            double h12;
            int n1;
            int n2;

            BoundaryNode **boundaryNodes;
            BoundaryElement **boundaryElements;

            Element ***grid;
            Element **elements;


            int nBoundaryNodes;
            int nBoundaryElements;
            int nElements;

            Mesh();
            Mesh(double origin1, double origin2, double h12, double n1, double n2);
            void addBoundaryNodes(int n, double *points);
            void createMesh(void);
            void getFirstElementPosition(BoundaryElement *element, int *index1, int *index2, double *edges);
            void draw(void);
    };
}

#endif // MESH_H
