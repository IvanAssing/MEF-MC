#include "element.h"
#include <cmath>

#define INTERSECTION_TOL 1.e-15
#define INVALID_KSI 10.0


MC::Element::Element()
{
}

MC::Element::Element(int index_):index(index_)
{
    edges = new double[4];

    adjacentElements = new Element*[4];

    intersections = new BoundaryIntersection[2];
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

}

bool MC::Element::findIntersection(MC::BoundaryElement *boundaryElement)
{
    int indexEdge = 0;

    double ksi1 = INVALID_KSI;
    double ksi2 = INVALID_KSI;

    if(this->intersections[0].element != NULL)
        indexEdge = normalizeEdge(this->intersections[0].edge + 2);

    double a, b, c, df=INTERSECTION_TOL;

    MC::Polynomial1D functionP, functionI;

    for(int i=0; i<3 && (ksi1 == INVALID_KSI && ksi2 == INVALID_KSI); i++, indexEdge++){

        indexEdge = normalizeEdge(indexEdge);

        if(indexEdge == this->intersections[0].edge)
            indexEdge = normalizeEdge(indexEdge+1);

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

    }

    if(ksi1+df<=1.0 && ksi1-df>=-1.0){
        this->intersections[1] = MC::BoundaryIntersection(boundaryElement, ksi1, indexEdge-1);
        return true;
    }

    if(ksi2+df<=1.0 && ksi2-df>=-1.0){
        this->intersections[1] = MC::BoundaryIntersection(boundaryElement, ksi2, indexEdge-1);
        return true;
    }


    return false;

}

int MC::Element::normalizeEdge(int edge)
{
    return (edge+16)%4;
}
