#include "triangleelement.h"

#include <GL/gl.h>
#include <cmath>
#include <QDebug>
#include <iostream>
#include <string>

MC::TriangleElement::TriangleElement()
{
}

MC::TriangleElement::TriangleElement(double x0, double y0, double x1, double y1, double x2, double y2,
                                     double x3, double y3, double x4, double y4, double x5, double y5)
{

    x1 = 0.5*(x0+x2);
    x3 = 0.5*(x4+x2);
    x5 = 0.5*(x4+x0);

    y1 = 0.5*(y0+y2);
    y3 = 0.5*(y4+y2);
    y5 = 0.5*(y4+y0);

    double coef[9];

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


//    coef[0] = x2; // 1
//    coef[1] = -1.*x0-3.*x2+4.*x5; // x
//    coef[2] = -1.*x1-3.*x2+4.*x4; // y
//    coef[3] = 4.*(x2+x3-x4-x5); // xy
//    coef[4] = 2.*(x1+x2-2.*x4); // x²
//    coef[5] = 2.*(x0+x2-2.*x5); // y²

    coef[0] = x4; // 1
    coef[1] = -x0-3.*x4+4.*x5; // x
    coef[2] = 2.*(x0-2.*x5+x4); // x²
    coef[3] = -x2-3.*x4+4.*x3; // y
    coef[4] = 4.*(x1-x3+x4-x5); // xy
    coef[5] = 0.0; // x²y
    coef[6] = 2.*(x2-2.*x3+x4); // y²
    coef[7] = 0.0; // y²x
    coef[8] = 0.0; // x²y²



    MC::Polynomial2D X(2,coef);

    coef[0] = y4; // 1
    coef[1] = -y0-3.*y4+4.*y5; // x
    coef[2] = 2.*(y0-2.*y5+y4); // x²
    coef[3] = -y2-3.*y4+4.*y3; // y
    coef[4] = 4.*(y1-y3+y4-y5); // xy
    coef[5] = 0.0; // x²y
    coef[6] = 2.*(y2-2.*y3+y4); // y²
    coef[7] = 0.0; // y²x
    coef[8] = 0.0; // x²y²


    MC::Polynomial2D Y(2,coef);

    std::cout<<"\nX = "<<X;
    std::cout<<"\nY = "<<Y;

    double dl = 0.01;

    glColor4d(0.5, 1.0, 0.5, 0.4);
    glPointSize(1.0);
    glBegin(GL_POINTS);{
        for(double l1=0.0; l1<=1.0; l1+=dl)
            for(double l2=0.0; l2<=1.0; l2+=dl)
                glVertex2d(X(l1,l2), Y(l1,l2));

    }
    glEnd();


    //    glColor3d(0.0, 1.0, 1.0);
    //    glLineWidth(2.);

    //    glBegin(GL_LINES);{
    //        glVertex2d(x0, y0);
    //        glVertex2d(x2, y2);

    //        glVertex2d(x2, y2);
    //        glVertex2d(x4, y4);

    //        glVertex2d(x4, y4);
    //        glVertex2d(x0, y0);
    //    }
    //    glEnd();

    //    glColor4d(0.0, 1.0, 0.5, 0.4);
    //    glBegin(GL_TRIANGLES);{
    //        glVertex2d(x0, y0);

    //        glVertex2d(x2, y2);

    //        glVertex2d(x4, y4);
    //    }
    //    glEnd();



}
