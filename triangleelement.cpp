#include "triangleelement.h"

#include <GL/gl.h>

MC::TriangleElement::TriangleElement()
{
}

MC::TriangleElement::TriangleElement(double x0, double y0, double x1, double y1, double x2, double y2,
                                     double x3, double y3, double x4, double y4, double x5, double y5)
{
    glColor3d(0.0, 1.0, 1.0);
    glLineWidth(2.);

    glBegin(GL_LINES);{
        glVertex2d(x0, y0);
        glVertex2d(x2, y2);

        glVertex2d(x2, y2);
        glVertex2d(x4, y4);

        glVertex2d(x4, y4);
        glVertex2d(x0, y0);
    }
    glEnd();

    glColor4d(0.0, 1.0, 0.5, 0.4);
    glBegin(GL_TRIANGLES);{
        glVertex2d(x0, y0);

        glVertex2d(x2, y2);

        glVertex2d(x4, y4);
    }
    glEnd();
}
