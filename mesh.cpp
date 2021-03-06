﻿#include "mesh.h"

#include <cmath>

#define INTERSECTION_TOLERANCE 1.e-10
#define INVALID_KSI 10.0

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


    ///
    glColor4d(0.9, 0.0, 0.0, 0.4);
    glBegin(GL_QUADS);
    {
        glVertex3d(elements[0]->edges[3], elements[0]->edges[0], 0.0);
        glVertex3d(elements[0]->edges[1], elements[0]->edges[0], 0.0);
        glVertex3d(elements[0]->edges[1], elements[0]->edges[2], 0.0);
        glVertex3d(elements[0]->edges[3], elements[0]->edges[2], 0.0);
    }
    glEnd();
    ///


    for(int i=nElementsUnderBoundary; i<nElements; i++)
        elements[i]->draw();



    for(int i=0; i<nBoundaryElements; i++)
        boundaryElements[i]->draw();

    //return;

    glColor4d(1.0, 1.0, 1.0, 0.5);
    glPointSize(16.f);

    //        for(int i=0; i<nElements; i++)
    //        {
    //            if(elements[i]->intersections[0].element != NULL)
    //                elements[i]->intersections[0].draw();

    //            //        if(elements[i]->nIntersections > 2)
    //            //            elements[i]->intersections[2].draw();
    //        }

    //        glColor4d(0.0, 0.0, 0.0, 0.5);
    //        glPointSize(8.f);
    //        for(int i=0; i<nElements; i++)
    //        {
    //            if(elements[i]->intersections[1].element != NULL)
    //                elements[i]->intersections[1].draw();

    //            //        if(elements[i]->nIntersections > 2)
    //            //            elements[i]->intersections[3].draw();
    //        }

    glColor4d(1.0, 0.0, 0.0, 1.0);
    glPointSize(5.0f);
    for(int i=0; i<nBoundaryNodes; i++)
        boundaryNodes[i]->draw();


//    for(int i=0; i<nElementEdges; i++)
//        elementEdges[i]->draw();

    for(int i=0; i<nElementsUnderBoundary; i++){
        //if(!elements[i]->nTriangles) continue;
        for(int j=0; j<elements[i]->nTriangles; j++)
            elements[i]->triangles[j].draw();
    }

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

    this->findLimits();

}

void MC::Mesh::findLimits(void)
{
    double max1, max2, min1, min2;

    max1 = boundaryNodes[0]->x;
    min1 = boundaryNodes[0]->x;
    max2 = boundaryNodes[0]->y;
    min2 = boundaryNodes[0]->y;

    for(int i=1; i<nBoundaryNodes; i++){
        if(boundaryNodes[i]->x > max1) max1 = boundaryNodes[i]->x;
        if(boundaryNodes[i]->x < min1) min1 = boundaryNodes[i]->x;
        if(boundaryNodes[i]->y > max2) max2 = boundaryNodes[i]->y;
        if(boundaryNodes[i]->y < min2) min2 = boundaryNodes[i]->y;
    }

    origin1 = min1 - (max1-min1)*0.1 - h12; // 10%
    origin2 = min2 - (max2-min2)*0.1 - h12; // 10%

    n1 = static_cast<int> (h12 + 1.2*(max1-min1)/h12) + 1;
    n2 = static_cast<int> (h12 + 1.2*(max2-min2)/h12) + 1;
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

    elementEdges= new ElementEdge*[n1*n2];
    nElementEdges= 0;

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
            elements[nElements] = new Element(nElements, index1, index2);
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

void MC::Mesh::getElementIndex(MC::BoundaryElement *element, int *index1, int *index2)
{
    *index1 = static_cast<int>(floor((element->nodes[0]->x - origin1)/h12));
    *index2 = static_cast<int>(floor((element->nodes[0]->y - origin2)/h12));
}


inline void findRoot(double a, double b, double c, double *ksi1, double *ksi2)
{
    if(fabs(c)<INTERSECTION_TOLERANCE){
        *ksi1 = -a/b;
        *ksi2 = INVALID_KSI;
    }
    else{
        double delta = b*b-4.*a*c;

        if(delta<0){ // Năo possui raizes reais
            *ksi1 = INVALID_KSI;
            *ksi2 = INVALID_KSI;
            return;
        }

        delta = sqrt(delta);

        *ksi1 = (-b + delta)/(2.*c);
        *ksi2 = (-b - delta)/(2.*c);
    }
}

MC::Element* MC::Mesh::createElement(int index1, int index2)
{
    if(grid[index1][index2] == NULL){
        elements[nElements] = new Element(nElements++, index1, index2);
        grid[index1][index2] = elements[nElements-1];
    }

    return grid[index1][index2];
}

void MC::Mesh::getEdges(int index1, int index2, double *edges)
{
    edges[3] = index1*h12+origin1; // x1
    edges[1] = (index1+1)*h12+origin1; // x0

    edges[0] = index2*h12+origin2; // y0
    edges[2] = (index2+1)*h12+origin2; // y1
}



void MC::Mesh::createMesh_2(void)
{
    elementEdges= new ElementEdge*[n1*n2];
    nElementEdges= 0;

    double ksi1 = INVALID_KSI;
    double ksi2 = INVALID_KSI;

    int index1, index2, indexBoundaryElement = 0;

    for(int i = 0; i<n1*n2 && indexBoundaryElement<nBoundaryElements; i++, indexBoundaryElement++){

        double a1 = boundaryElements[indexBoundaryElement]->curveX.an[0] - origin1;
        double b1 = boundaryElements[indexBoundaryElement]->curveX.an[1];
        double c1 = boundaryElements[indexBoundaryElement]->curveX.an[2];

        double a2 = boundaryElements[indexBoundaryElement]->curveY.an[0] - origin2;
        double b2 = boundaryElements[indexBoundaryElement]->curveY.an[1];
        double c2 = boundaryElements[indexBoundaryElement]->curveY.an[2];




        getElementIndex(boundaryElements[indexBoundaryElement], &index1, &index2);

        bool notStop;

        int indexFound;

        // x <-
        notStop = true;
        for(int i=index1; notStop; i--){
            notStop=false;
            findRoot(a1-i*h12, b1, c1, &ksi1, &ksi2);

            if(ksi1+INTERSECTION_TOLERANCE<=1.0 && ksi1-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveY(ksi1) - origin2)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(i, i-1, indexFound, indexFound, boundaryElements[indexBoundaryElement], ksi1, (b1+2.0*c1*ksi1>=0)? +1:-1);
                notStop = true;
            }
            if(ksi2+INTERSECTION_TOLERANCE<=1.0 && ksi2-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveY(ksi2) - origin2)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(i, i-1, indexFound, indexFound, boundaryElements[indexBoundaryElement], ksi2, (b1+2.0*c1*ksi2>=0)? +1:-1);
                notStop = true;
            }

        }

        // x ->
        notStop = true;
        for(int i=index1+1; notStop; i++){
            notStop=false;
            findRoot(a1-i*h12, b1, c1, &ksi1, &ksi2);

            if(ksi1+INTERSECTION_TOLERANCE<=1.0 && ksi1-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveY(ksi1) - origin2)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(i-1, i, indexFound, indexFound, boundaryElements[indexBoundaryElement], ksi1, (b1+2.0*c1*ksi1>=0)? +1:-1);
                notStop = true;
            }
            if(ksi2+INTERSECTION_TOLERANCE<=1.0 && ksi2-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveY(ksi2) - origin2)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(i-1, i, indexFound, indexFound, boundaryElements[indexBoundaryElement], ksi2, (b1+2.0*c1*ksi2>=0)? +1:-1);
                notStop = true;
            }

        }

        // y <-
        notStop = true;
        for(int i=index2; notStop; i--){
            notStop=false;
            findRoot(a2-i*h12, b2, c2, &ksi1, &ksi2);

            if(ksi1+INTERSECTION_TOLERANCE<=1.0 && ksi1-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveX(ksi1) - origin1)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(indexFound, indexFound, i, i-1, boundaryElements[indexBoundaryElement], ksi1, (b2+2.0*c2*ksi1>=0)? +2:-2);
                notStop = true;
            }
            if(ksi2+INTERSECTION_TOLERANCE<=1.0 && ksi2-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveX(ksi2) - origin1)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(indexFound, indexFound, i, i-1, boundaryElements[indexBoundaryElement], ksi2, (b2+2.0*c2*ksi2>=0)? +2:-2);
                notStop = true;
            }

        }

        // y ->
        notStop = true;
        for(int i=index2+1; notStop; i++){
            notStop=false;
            findRoot(a2-i*h12, b2, c2, &ksi1, &ksi2);

            if(ksi1+INTERSECTION_TOLERANCE<=1.0 && ksi1-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveX(ksi1) - origin1)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(indexFound, indexFound, i-1, i, boundaryElements[indexBoundaryElement], ksi1, (b2+2.0*c2*ksi1>=0)? +2:-2);
                notStop = true;
            }
            if(ksi2+INTERSECTION_TOLERANCE<=1.0 && ksi2-INTERSECTION_TOLERANCE>=-1.0){
                indexFound = static_cast<int>(floor((boundaryElements[indexBoundaryElement]->curveX(ksi2) - origin1)/h12));
                elementEdges[nElementEdges++] = new MC::ElementEdge(indexFound, indexFound, i-1, i, boundaryElements[indexBoundaryElement], ksi2, (b2+2.0*c2*ksi2>=0)? +2:-2);
                notStop = true;
            }
        }
    }

    /////////////////////
    grid = new Element**[n1];
    for(int i=0; i<n1; i++)
        grid[i] = new Element*[n2];

    for(int i=0; i<n1; i++)
        for(int j=0; j<n2; j++)
            grid[i][j] = NULL;

    elements = new Element*[n1*n2];
    nElements = 0;

    //MC::Element* currentElement;
    double edges[4];

    for(int i=0; i<nElementEdges; i++){

        /*// TESTE
        std::cout<<"\n\n IE: "<<i<<" \ DIR: "<<elementEdges[i]->dir;
        std::cout<<"\n 1: "<<elementEdges[i]->indexH1<<" - "<<elementEdges[i]->indexV1<<"\n 2: "<<elementEdges[i]->indexH2<<" - "<<elementEdges[i]->indexV2;
        std::cout<<"\n "<<elementEdges[i]->element<<" / "<<elementEdges[i]->ksi;
        //*/

        int edgeIndex = elementEdges[i]->getEdgeIndex();

        index1 = elementEdges[i]->indexH1;
        index2 = elementEdges[i]->indexV1;

        if(grid[index1][index2] == NULL){
            elements[nElements] = new Element(nElements, index1, index2);
            grid[index1][index2] = elements[nElements++];

            getEdges(index1, index2, edges);
            grid[index1][index2]->setEdges(edges);
        }

        grid[index1][index2]->setIntersection(MC::Output, MC::BoundaryIntersection(elementEdges[i]->element, elementEdges[i]->ksi, edgeIndex));

        index1 = elementEdges[i]->indexH2;
        index2 = elementEdges[i]->indexV2;

        if(grid[index1][index2] == NULL){
            elements[nElements] = new Element(nElements, index1, index2);
            grid[index1][index2] = elements[nElements++];


            getEdges(index1, index2, edges);
            grid[index1][index2]->setEdges(edges);

        }

        grid[index1][index2]->setIntersection(MC::Input, MC::BoundaryIntersection(elementEdges[i]->element, elementEdges[i]->ksi, MC::Element::normalizeEdge(edgeIndex+2)));


        grid[elementEdges[i]->indexH1][elementEdges[i]->indexV1]->adjacentElements[edgeIndex] =
                grid[elementEdges[i]->indexH2][elementEdges[i]->indexV2];
        grid[elementEdges[i]->indexH2][elementEdges[i]->indexV2]->adjacentElements[MC::Element::normalizeEdge(edgeIndex+2)] =
                grid[elementEdges[i]->indexH1][elementEdges[i]->indexV1];


        setExternalLinks(elementEdges[i]->indexH1, elementEdges[i]->indexV1, edgeIndex);


    }

    for(int i=0; i<nElements; i++){
        if(elements[i]->intersections[0].edge == elements[i]->intersections[1].edge)
            elements[i]->adjacentElements[MC::Element::normalizeEdge(elements[i]->intersections[0].edge+2)]=
                    elements[i];
    }

    nElementsUnderBoundary = nElements;

    for(int i=0; i<nElements; i++)
        setInternalLinks(elements[i]);

//    for(int i=0; i<nElementsUnderBoundary; i++)
//        //elements[i]->findTriangleDivision();
//        elements[i]->findTriangleDivision_2();

    for(int i=0; i<nElementsUnderBoundary; i++)
        elements[i]->findTriangleDivision_3();


    //for(int i=0; i<nElementsUnderBoundary; i++)
    //        elements[29]->findTriangleDivision();
}



void MC::Mesh::setExternalLinks(int index1, int index2, int edge)
{


    if(edge == 2){
        if(grid[index1+1][index2] == NULL)
            grid[index1][index2]->adjacentElements[1] = grid[index1][index2];
        else{
            grid[index1][index2]->adjacentElements[1] = grid[index1+1][index2];
            grid[index1+1][index2]->adjacentElements[3] = grid[index1][index2];
        }
        if(grid[index1+1][index2+1] == NULL)
            grid[index1][index2+1]->adjacentElements[1] = grid[index1][index2+1];
        else{
            grid[index1][index2+1]->adjacentElements[1] = grid[index1+1][index2+1];
            grid[index1+1][index2+1]->adjacentElements[3] = grid[index1][index2+1];
        }
        return;
    }
    if(edge == 1){
        if(grid[index1][index2-1] == NULL)
            grid[index1][index2]->adjacentElements[0] = grid[index1][index2];
        else{
            grid[index1][index2]->adjacentElements[0] = grid[index1][index2-1];
            grid[index1][index2-1]->adjacentElements[2] = grid[index1][index2];
        }
        if(grid[index1+1][index2-1] == NULL)
            grid[index1+1][index2]->adjacentElements[0] = grid[index1+1][index2];
        else{
            grid[index1+1][index2]->adjacentElements[0] = grid[index1+1][index2-1];
            grid[index1+1][index2-1]->adjacentElements[2] = grid[index1+1][index2];
        }
        return;
    }
    if(edge == 0){
        if(grid[index1-1][index2] == NULL)
            grid[index1][index2]->adjacentElements[3] = grid[index1][index2];
        else{
            grid[index1][index2]->adjacentElements[3] = grid[index1-1][index2];
            grid[index1-1][index2]->adjacentElements[1] = grid[index1][index2];
        }
        if(grid[index1-1][index2-1] == NULL)
            grid[index1][index2-1]->adjacentElements[3] = grid[index1][index2-1];
        else{
            grid[index1][index2-1]->adjacentElements[3] = grid[index1-1][index2-1];
            grid[index1-1][index2-1]->adjacentElements[1] = grid[index1][index2-1];
        }
        return;
    }
    if(edge == 3){
        if(grid[index1][index2+1] == NULL)
            grid[index1][index2]->adjacentElements[2] = grid[index1][index2];
        else{
            grid[index1][index2]->adjacentElements[2] = grid[index1][index2+1];
            grid[index1][index2+1]->adjacentElements[0] = grid[index1][index2];
        }
        if(grid[index1-1][index2+1] == NULL)
            grid[index1-1][index2]->adjacentElements[2] = grid[index1-1][index2];
        else{
            grid[index1-1][index2]->adjacentElements[2] = grid[index1-1][index2+1];
            grid[index1-1][index2+1]->adjacentElements[0] = grid[index1-1][index2];
        }
        return;
    }
}

inline void getAdjacentElementIndex(int edge, int *index1, int *index2)
{
    switch(edge){
        case 0 : {--*index2; return;}
        case 1 : {++*index1; return;}
        case 2 : {++*index2; return;}
        case 3 : {--*index1; return;}
    }
}

void MC::Mesh::setInternalLinks(MC::Element *element)
{
    double edges[4];
    int index1 = element->index1;
    int index2 = element->index2;


    for(int i=0; i<4; i++){
        if(element->adjacentElements[i] == NULL){
            getAdjacentElementIndex(i, &index1, &index2);
            if(index1<0 || index2<0 || index1>=n1 || index2>=n2) return;
            if(grid[index1][index2] == NULL){
                elements[nElements] = new Element(nElements, index1, index2);
                grid[index1][index2] = elements[nElements++];

                getEdges(index1, index2, edges);
                grid[index1][index2]->setEdges(edges);
            }

            element->adjacentElements[i] = grid[index1][index2];
            grid[index1][index2]->adjacentElements[MC::Element::normalizeEdge(i+2)] = element;
        }
    }


}

double MC::Mesh::evalArea(void)
{
    double sum = 0.0;

    double cte = 1.0;

    Polynomial2D f(0,&cte);

    for(int i=0; i<nElementsUnderBoundary; i++)
        for(int j=0; j<elements[i]->nTriangles; j++)
            sum += elements[i]->triangles[j].evalIntegral(f);

    for(int i=nElementsUnderBoundary; i<nElements; i++)
        sum += h12*h12;

    return sum;
}
