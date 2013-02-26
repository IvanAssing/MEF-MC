#ifndef TRIANGLEELEMENT_H
#define TRIANGLEELEMENT_H

#include "polynomial2d.h"
#include "graphic.h"

namespace MC
{

    class TriangleElement : public Graphic
    {
        public:
            TriangleElement();
            TriangleElement(double x0, double y0, double x1, double y1, double x2, double y2,
                            double x3, double y3, double x4, double y4, double x5, double y5);

            double *pts;
            double *w,*px,*py;

            Polynomial2D *N;

            Polynomial2D X,Y;

            void updateWPGauss(void);
            double evalIntegral(Polynomial2D &function);

            virtual void draw(void);
    };
}

#endif // TRIANGLEELEMENT_H
