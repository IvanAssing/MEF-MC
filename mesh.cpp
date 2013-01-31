#include "mesh.h"

#include <cmath>

MC::Mesh::Mesh()
{
}

MC::Mesh::Mesh(double origin1_, double origin2_, double h12_, double n1_, double n2_)
    :origin1(origin1_), origin2(origin2_), h12(h12_), n1(n1_), n2(n2_)
{

}

void MC::Mesh::draw(void)
{
    glColor4d(0.9, 0.9, 0.9, 0.9);
    glLineWidth(0.5f);

    glBegin(GL_LINES);
    {
        double ix=origin1;
        double iy=origin2 + n2*h12;

        for(int nx=0; nx<=n1; ix+=h12, nx++){
            glVertex3d(ix, origin2, 0.);
            glVertex3d(ix, iy, 0.);
        }

        ix=origin1 + n1*h12;
        iy=origin2;

        for(int ny=0; ny<=n2; iy+=h12, ny++){

            glVertex3d(origin1, iy, 0.);
            glVertex3d(ix, iy, 0.);
        }
    }
    glEnd();

    for(int i=0; i<nElements; i++)
        elements[i]->draw();

    for(int i=0; i<nBoundaryElements; i++)
        boundaryElements[i]->draw();

    glColor4d(1.0, 1.0, 1.0, 0.5);
    glPointSize(16.f);
    for(int i=0; i<nElements; i++)
    {
        if(elements[i]->intersections[0].element != NULL)
            elements[i]->intersections[0].draw();

//        if(elements[i]->nIntersections > 2)
//            elements[i]->intersections[2].draw();
    }

    glColor4d(0.0, 0.0, 0.0, 0.5);
    glPointSize(8.f);
    for(int i=0; i<nElements; i++)
    {
        if(elements[i]->intersections[1].element != NULL)
            elements[i]->intersections[1].draw();

//        if(elements[i]->nIntersections > 2)
//            elements[i]->intersections[3].draw();
    }

    glColor4d(1.0, 0.0, 0.0, 1.0);
    glPointSize(5.0f);
    for(int i=0; i<nBoundaryNodes; i++)
        boundaryNodes[i]->draw();
}


void MC::Mesh::addBoundaryNodes(int n, double *points)
{
    // Nós do contorno
    nBoundaryNodes = n;
    boundaryNodes = new MC::BoundaryNode*[nBoundaryNodes];

    for(int i=0; i<nBoundaryNodes; i++)
        boundaryNodes[i] = new MC::BoundaryNode(i, points[2*i], points[2*i+1]);

    // Elementos do contorno
    nBoundaryElements = nBoundaryNodes/2;

    boundaryElements = new MC::BoundaryElement*[nBoundaryElements];

    for(int i=0; i<nBoundaryElements-1; i++)
        boundaryElements[i] =
                new MC::BoundaryElement(boundaryNodes[2*i], boundaryNodes[2*i+1], boundaryNodes[2*i+2]);

    boundaryElements[nBoundaryElements-1] =
            new MC::BoundaryElement(boundaryNodes[nBoundaryNodes-2],
            boundaryNodes[nBoundaryNodes-1], boundaryNodes[0]);
}


void MC::Mesh::createMesh(void)
{
    grid = new Element**[n1];
    for(int i=0; i<n1; i++)
        grid[i] = new Element*[n2];

    for(int i=0; i<n1; i++)
        for(int j=0; j<n2; j++)
            grid[i][j] = NULL;

    elements = new Element*[n1*n2];
    nElements = 0;

    double edge[4];

    int index1;
    int index2;

    int indexBoundaryElement = 0;
    int indexFirstElement = 0;
    int indexElement = 0;

    Element *currentElement;

    getFirstElementPosition(boundaryElements[indexBoundaryElement],
                            &index1, &index2, edge);


    int temp = 0;

    bool flag = true;

    BoundaryIntersection inputIntersection = MC::BoundaryIntersection(boundaryElements[0], 10., 0);

    for(int i = 0; i<n1*n2 && indexBoundaryElement<nBoundaryElements; i++){


        if(grid[index1][index2] == NULL){
            elements[nElements] = new Element(nElements);
            indexElement = nElements++;
            grid[index1][index2] = elements[indexElement];
        }
        else{
            indexElement = grid[index1][index2]->index;
        }

        currentElement = grid[index1][index2];

        if(flag)
            currentElement->setIntersection(MC::Input, inputIntersection);
        else
            flag = true;

        currentElement->setEdges(edge);

        if(temp == 42)
        {
            temp = 42;
        }

        if(!currentElement->findIntersection(boundaryElements[indexBoundaryElement])){
            indexBoundaryElement++;
            flag = false;
            continue;
        }

        inputIntersection = currentElement->intersections[currentElement->nIntersections-1];
        inputIntersection.edge = MC::Element::normalizeEdge(inputIntersection.edge + 2);

        switch(currentElement->intersections[currentElement->nIntersections-1].edge)
        {
            case 0 : { edge[2] = edge[0] , edge[0] -= this->h12 , index2 -= 1; break; }
            case 1 : { edge[3] = edge[1] , edge[1] += this->h12 , index1 += 1; break; }
            case 2 : { edge[0] = edge[2] , edge[2] += this->h12 , index2 += 1; break; }
            case 3 : { edge[1] = edge[3] , edge[3] -= this->h12 , index1 -= 1; break; }
        }
    }




}



void MC::Mesh::getFirstElementPosition(MC::BoundaryElement *element, int *index1, int *index2, double *edges)
{
    *index1 = (int) floor((element->nodes[0]->x - origin1)/h12);
    *index2 = (int) floor((element->nodes[0]->y - origin2)/h12);

    edges[3] = *index1*h12+origin1; // x1
    edges[1] = (*index1+1)*h12+origin1; // x0

    edges[0] = *index2*h12+origin2; // y0
    edges[2] = (*index2+1)*h12+origin2; // y1
}


