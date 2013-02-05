#ifndef MESH_H
#define MESH_H

#include "node.h"
#include "boundarynode.h"
#include "element.h"
#include "boundaryelement.h"
#include "elementedge.h"


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
            ElementEdge **elementEdges;

            Element ***grid;
            Element **elements;


            int nBoundaryNodes;
            int nBoundaryElements;
            int nElements;
            int nElementEdges;

            Mesh();
            Mesh(double origin1, double origin2, double h12, double n1, double n2);
            void addBoundaryNodes(int n, double *points);
            void findLimits(void);
            void createMesh(void);
            void createMesh_2(void);
            void getFirstElementPosition(BoundaryElement *element, int *index1, int *index2, double *edges);
            void getElementIndex(BoundaryElement *element, int *index1, int *index2);

            Element* createElement(int index1, int index2);
            void getEdges(int index1, int index2, double *edges);

            void setExternalLinks(int index1, int index2, int edge);
            void setInternalLinks(Element *element);

            void draw(void);
    };
}

#endif // MESH_H
