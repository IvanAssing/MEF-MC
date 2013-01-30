#include "boundaryintersection.h"

MC::BoundaryIntersection::BoundaryIntersection()
{
    element = NULL;
}

MC::BoundaryIntersection::BoundaryIntersection(BoundaryElement *element_, double ksi_, int edge_)
    :element(element_), ksi(ksi_), edge(edge_)
{

}


void MC::BoundaryIntersection::draw(void)
{
    glColor4d(1.0, 0.1, 1.0, 1.0);
    glPointSize(10.f);

    glBegin(GL_POINTS);
    {
        glVertex2d(element->curveX(ksi),
                element->curveY(ksi));
    }
    glEnd();
}
