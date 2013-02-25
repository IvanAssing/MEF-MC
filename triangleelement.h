#ifndef TRIANGLEELEMENT_H
#define TRIANGLEELEMENT_H

#include "polynomial2d.h"

namespace MC
{

    class TriangleElement
    {
        public:
            TriangleElement();
            TriangleElement(double x0, double y0, double x1, double y1, double x2, double y2,
                            double x3, double y3, double x4, double y4, double x5, double y5);

            Polynomial2D L1, L2, L3;
    };
}

#endif // TRIANGLEELEMENT_H
