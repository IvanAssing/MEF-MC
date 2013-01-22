#ifndef FUNCTOR2D_H
#define FUNCTOR2D_H

namespace MC{
class Functor2D
{
public:
    Functor2D();
    virtual double operator()(double v1, double v2)=0;
};
}

#endif // FUNCTOR2D_H
