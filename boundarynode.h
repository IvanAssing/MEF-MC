#ifndef BOUNDARYNODE_H
#define BOUNDARYNODE_H

#include "graphic.h"

namespace MC
{
    class BoundaryNode : public Graphic
    {
        public:
            int index;
            double x;
            double y;


            BoundaryNode();
            BoundaryNode(int index, double x, double y);

            void draw(void);

    };
}

#endif // BOUNDARYNODE_H
