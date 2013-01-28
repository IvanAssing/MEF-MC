#include "mesh.h"

#include <cmath>

MC::Mesh::Mesh()
{
}

MC::Mesh::Mesh(double origin1, double origin2, double h12, double n1, double n2)
    :origin1(origin1), origin2(origin2), h12(h12), n1(n1), n2(n2)
{

}

void MC::Mesh::draw(void)
{
    glColor4d(0.5, 0.5, 0.5, 0.6);
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

    for(int i=0; i<nBoundaryElements; i++)
        boundaryElements[i]->draw();

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
        for(int j=0; j<n1; j++)
            grid[i][j] = NULL;

    elements = new Element*[n1*n2];


    double edge[4];

    int index1;
    int index2;

    int indexBoundaryElement = 0;
    int indexFirstElement = 0;


    while(indexBoundaryElement = nBoundaryElements){

        getFirstElementPosition(boundaryElements[indexBoundaryElement],
                                &index1, &index2, edge);


    }




}



void MC::Mesh::getFirstElementPosition(MC::BoundaryElement *element, int *index1, int *index2, double *edges)
{
    *index1 = (int) floor((element->nodes[0]->x - origin1)/h12);
    *index2 = (int) floor((element->nodes[0]->y - origin2)/h12);

    edges[1] = *index1*h12+origin1; // x0
    edges[3] = (*index1+1)*h12+origin1; // x1

    edges[0] = *index2*h12+origin2; // y0
    edges[2] = (*index2+1)*h12+origin2; // y1
}
