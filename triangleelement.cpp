#include "triangleelement.h"

#include <GL/gl.h>
#include <cmath>

MC::TriangleElement::TriangleElement()
{
}

MC::TriangleElement::TriangleElement(double x0, double y0, double x1, double y1, double x2, double y2,
                                     double x3, double y3, double x4, double y4, double x5, double y5)
{
    double coef[3];

    this->N = new MC::Polynomial2D[6];

    double triangleArea_inv2 = 1.0/fabs((x2*y4+x0*y2+y0*x4) - (y0*x2+y2*x4+y4*x0));

    // L1
    coef[0] = (x2*y4 - x4*y2)*triangleArea_inv2;
    coef[1] = (y2 - y4)*triangleArea_inv2;
    coef[2] = (x4 - x2)*triangleArea_inv2;

    MC::Polynomial2D L1(1,coef);


    // L2
    coef[0] = (x4*y0 - x0*y4)*triangleArea_inv2;
    coef[1] = (y4 - y0)*triangleArea_inv2;
    coef[2] = (x0 - x4)*triangleArea_inv2;

    MC::Polynomial2D L2(1,coef);


    // L3
    coef[0] = (x0*y2 - x2*y0)*triangleArea_inv2;
    coef[1] = (y0 - y2)*triangleArea_inv2;
    coef[2] = (x2 - x0)*triangleArea_inv2;

    MC::Polynomial2D L3(1,coef);


    N[0] = L1*L1*2.0-L1; //(2.0*L1-1)*L1;
    N[2] = L2*L2*2.0-L2;
    N[4] = L3*L3*2.0-L3;

    N[1] = L1*L2*4.0;
    N[3] = L2*L3*4.0;
    N[5] = L3*L1*4.0;








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
