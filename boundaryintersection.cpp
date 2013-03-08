#include "boundaryintersection.h"

MC::BoundaryIntersection::BoundaryIntersection()
{
    element = NULL;
    ksi = 10;
    edge = 0;
}

MC::BoundaryIntersection::BoundaryIntersection(BoundaryElement *element_, double ksi_, int edge_)
    :element(element_), ksi(ksi_), edge(edge_)
{

}


void MC::BoundaryIntersection::draw(void)
{


    glBegin(GL_POINTS);
    {
        glVertex2d(element->curveX(ksi),
                element->curveY(ksi));
    }
    glEnd();
}

double MC::BoundaryIntersection::valueEdge(int edge)
{
    if(edge%2)
        return element->curveY(ksi);
    else
        return element->curveX(ksi);
}
