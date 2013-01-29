#include "element.h"

MC::Element::Element()
{
}

MC::Element::Element(int index):index(index)
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
    glColor4d(0.1, 0.2, 0.8, 0.6);


    glBegin(GL_QUADS);
    {
        glVertex3d(edges[1], edges[0], 0.0);
        glVertex3d(edges[3], edges[0], 0.0);
        glVertex3d(edges[3], edges[2], 0.0);
        glVertex3d(edges[1], edges[2], 0.0);
    }
    glEnd();

    glColor4d(0.0, 1.0, 0.0, 0.8);
    glLineWidth(2.5f);

    glBegin(GL_LINE_LOOP);
    {
        glVertex3d(edges[1], edges[0], 0.0);
        glVertex3d(edges[3], edges[0], 0.0);
        glVertex3d(edges[3], edges[2], 0.0);
        glVertex3d(edges[1], edges[2], 0.0);
    }
    glEnd();
}
