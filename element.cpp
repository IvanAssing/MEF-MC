#include "element.h"
#include <cmath>

#define INTERSECTION_TOL 1.e-10
#define INVALID_KSI 10.0


MC::Element::Element()
{
}

MC::Element::Element(int index_, int index1_, int index2_):index(index_), index1(index1_), index2(index2_)
{
    edges = new double[4];

    adjacentElements = new Element*[4];

    adjacentElements[0] = NULL;
    adjacentElements[1] = NULL;
    adjacentElements[2] = NULL;
    adjacentElements[3] = NULL;


    nIntersections = 0;
}

void MC::Element::setEdges(double *edges_)
{
    edges[0] = edges_[0];
    edges[1] = edges_[1];
    edges[2] = edges_[2];
    edges[3] = edges_[3];
}

void MC::Element::draw(void)
{
    glColor4d(0.9, 0.9, 0.9, 0.6);


    glBegin(GL_QUADS);
    {
        glVertex3d(edges[3], edges[0], 0.0);
        glVertex3d(edges[1], edges[0], 0.0);
        glVertex3d(edges[1], edges[2], 0.0);
        glVertex3d(edges[3], edges[2], 0.0);
    }
    glEnd();

    glColor4d(0.0, 1.0, 0.0, 0.8);
    glLineWidth(2.5f);

    glBegin(GL_LINE_LOOP);
    {
        glVertex3d(edges[3], edges[0], 0.0);
        glVertex3d(edges[1], edges[0], 0.0);
        glVertex3d(edges[1], edges[2], 0.0);
        glVertex3d(edges[3], edges[2], 0.0);
    }
    glEnd();


    glLineWidth(4.5f);
    glBegin(GL_LINES);
    {
        (adjacentElements[0]) ? glColor4d(1.0, 0.0, 0.0, 0.8) : glColor4d(0.0, 1.0, 0.0, 0.8);
        glVertex3d(edges[3], edges[0], 0.0);
        glVertex3d(edges[1], edges[0], 0.0);
        (adjacentElements[1]) ? glColor4d(1.0, 0.0, 0.0, 0.8) : glColor4d(0.0, 1.0, 0.0, 0.8);
        glVertex3d(edges[1], edges[0], 0.0);
        glVertex3d(edges[1], edges[2], 0.0);
        (adjacentElements[2]) ? glColor4d(1.0, 0.0, 0.0, 0.8) : glColor4d(0.0, 1.0, 0.0, 0.8);
        glVertex3d(edges[1], edges[2], 0.0);
        glVertex3d(edges[3], edges[2], 0.0);
        (adjacentElements[3]) ? glColor4d(1.0, 0.0, 0.0, 0.8) : glColor4d(0.0, 1.0, 0.0, 0.8);
        glVertex3d(edges[3], edges[2], 0.0);
        glVertex3d(edges[3], edges[0], 0.0);
    }
    glEnd();

}

bool MC::Element::findIntersection(MC::BoundaryElement *boundaryElement)
{
    int indexEdge = 0;

    double ksi1 = INVALID_KSI;
    double ksi2 = INVALID_KSI;

    //if(this->intersections[0].element != NULL)
    indexEdge = normalizeEdge(this->intersections[nIntersections-2].edge + 2);

    double a, b, c, df=INTERSECTION_TOL;

    MC::Polynomial1D functionP, functionI;

    for(int i=0; i<4 /*&& (ksi1 == INVALID_KSI && ksi2 == INVALID_KSI)*/; i++, indexEdge++){

        indexEdge = normalizeEdge(indexEdge);

        //        if(indexEdge == this->intersections[0].edge)
        //            indexEdge = normalizeEdge(indexEdge+1);

        if(indexEdge % 2 == 0){
            functionP = boundaryElement->curveY;
            functionI = boundaryElement->curveX;
        }
        else
        {
            functionP = boundaryElement->curveX;
            functionI = boundaryElement->curveY;
        }


        a = functionP.an[0];
        b = functionP.an[1];
        c = functionP.an[2];

        a -= this->edges[indexEdge];


        double delta = b*b-4.*a*c;


        if(delta<0) // Năo possui raizes reais
        {
            continue;
        }


        if(fabs(c)<INTERSECTION_TOL){
            ksi1 = -a/b;
            ksi2 = INVALID_KSI;
        }
        else{
            ksi1 = (-b + sqrt(delta))/(2.*c);
            ksi2 = (-b - sqrt(delta))/(2.*c);
        }



        double fi, f0, f1;

        int if0 = normalizeEdge(indexEdge - 1);
        int if1 = normalizeEdge(indexEdge + 1);

        f0 = edges[if0];
        f1 = edges[if1];

        if(ksi1+df<=1.0 && ksi1-df>=-1.0)
        {
            fi = functionI(ksi1);
            if(!((fi+df>=f0&&fi-df<=f1)||(fi-df<=f0&&fi+df>=f1)))
                ksi1 = INVALID_KSI;

        }
        else
            ksi1 = INVALID_KSI;


        if(ksi2 != INVALID_KSI)
        {
            if(ksi2+df<=1.0 && ksi2-df>=-1.0)
            {
                fi = functionI(ksi2);
                if(!((fi+df>=f0&&fi-df<=f1)||(fi-df<=f0&&fi+df>=f1)))
                    ksi2 = INVALID_KSI;
            }
            else
                ksi2 = INVALID_KSI;
        }



        if(ksi1!= INVALID_KSI && ksi2!= INVALID_KSI)
        {
            df = 0; // somente teste
        }

        if(ksi1+df<=1.0 && ksi1-df>=-1.0 && fabs(ksi1-this->intersections[nIntersections-2].ksi)>INTERSECTION_TOL){
            this->setIntersection(MC::Output, MC::BoundaryIntersection(boundaryElement, ksi1, indexEdge));
            return true;
        }

        if(ksi2+df<=1.0 && ksi2-df>=-1.0 && fabs(ksi2-this->intersections[nIntersections-2].ksi)>INTERSECTION_TOL){
            this->setIntersection(MC::Output,MC::BoundaryIntersection(boundaryElement, ksi2, indexEdge));
            return true;
        }

    }


    return false;

}

int MC::Element::normalizeEdge(int edge)
{
    return (edge+16)%4;
}

void MC::Element::setIntersection(MC::TypeIntersection type_, BoundaryIntersection intersection_)
{
    if(type_ == MC::Output){

        if(nIntersections == 0){
            intersections = new MC::BoundaryIntersection[2];
            nIntersections = 2;

            intersections[1] = intersection_;

            return;
        }
        else if(intersections[1].element == NULL){
            intersections[1] = intersection_;

            return;
        }
        else{
            MC::BoundaryIntersection copy0 = intersections[0];
            MC::BoundaryIntersection copy1 = intersections[1];

            delete intersections;
            intersections = new MC::BoundaryIntersection[4];
            nIntersections = 4;

            intersections[0] = copy0;
            intersections[1] = copy1;

            intersections[3] = intersection_;

            return;
        }

    }

    if(type_ == MC::Input){

        if(nIntersections == 0){
            intersections = new MC::BoundaryIntersection[2];
            nIntersections = 2;

            intersections[0] = intersection_;

            return;
        }
        else if(intersections[0].element == NULL){
            intersections[0] = intersection_;

            return;
        }
        else{
            MC::BoundaryIntersection copy0 = intersections[0];
            MC::BoundaryIntersection copy1 = intersections[1];

            delete intersections;
            intersections = new MC::BoundaryIntersection[4];
            nIntersections = 4;

            intersections[0] = copy0;
            intersections[1] = copy1;

            intersections[2] = intersection_;

            return;
        }

    }
}


void MC::Element::findTriangleDivision(void)
{
    double *pts = new double[100];


    double pts_vertex[4][2];

    int np = 0;



    pts_vertex[0][0] = edges[1];
    pts_vertex[0][1] = edges[0];
    pts_vertex[1][0] = edges[1];
    pts_vertex[1][1] = edges[2];
    pts_vertex[2][0] = edges[3];
    pts_vertex[2][1] = edges[2];
    pts_vertex[3][0] = edges[3];
    pts_vertex[3][1] = edges[0];

    pts[np++] = intersections[0].element->curveX(intersections[0].ksi);
    pts[np++] = intersections[0].element->curveY(intersections[0].ksi);

    if(intersections[0].element == intersections[1].element){
        pts[np++] = intersections[0].element->curveX(0.5*(intersections[0].ksi+intersections[1].ksi));
        pts[np++] = intersections[0].element->curveY(0.5*(intersections[0].ksi+intersections[1].ksi));
    }
    else{
        pts[np++] = intersections[0].element->curveX(0.5*(intersections[0].ksi+1.));
        pts[np++] = intersections[0].element->curveY(0.5*(intersections[0].ksi+1.));

        pts[np++] = intersections[0].element->nodes[2]->x;
        pts[np++] = intersections[0].element->nodes[2]->y;

        pts[np++] = intersections[1].element->curveX(0.5*(intersections[1].ksi-1.));
        pts[np++] = intersections[1].element->curveY(0.5*(intersections[1].ksi-1.));
    }

    pts[np++] = intersections[1].element->curveX(intersections[1].ksi);
    pts[np++] = intersections[1].element->curveY(intersections[1].ksi);

    double prev_x = intersections[1].element->curveX(intersections[1].ksi);
    double prev_y = intersections[1].element->curveY(intersections[1].ksi);

    int iEdgeIntBegin = intersections[1].edge;
    int iEdgeIntEnd = intersections[0].edge;

    int ie, ne = iEdgeIntEnd-iEdgeIntBegin;

    if(ne <=0) ne +=4;

    for(int i=0, ie = iEdgeIntBegin; i<ne; i++, ie = normalizeEdge(ie+1)){
        pts[np++] = 0.5*(prev_x + pts_vertex[ie][0]);
        pts[np++] = 0.5*(prev_y + pts_vertex[ie][1]);
        pts[np++] = pts_vertex[ie][0];
        pts[np++] = pts_vertex[ie][1];
        prev_x = pts_vertex[ie][0];
        prev_y = pts_vertex[ie][1];
    }

    pts[np++] = 0.5*(prev_x + intersections[0].element->curveX(intersections[0].ksi));
    pts[np++] = 0.5*(prev_y + intersections[0].element->curveY(intersections[0].ksi));


    glColor3d(0.0, 1.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    for(int i=0; i<np; i+=2)
        glVertex2d(pts[i], pts[i+1]);
    glEnd();

    double med_x = 0;
    double med_y = 0;

    for(int i=0; i<np; i+=2){
        med_x += pts[i];
        med_y += pts[i+1];
    }

    med_x /= 0.5*np;
    med_y /= 0.5*np;


    glBegin(GL_POINTS);
    glVertex2d(med_x, med_y);
    glEnd();

    glColor3d(0.0, 1.0, 1.0);
    glLineWidth(2.);
    glBegin(GL_LINES);
    for(int i=0; i<np; i+=4){
        glVertex2d(med_x, med_y);
        glVertex2d(pts[i], pts[i+1]);
    }
    glEnd();



}

