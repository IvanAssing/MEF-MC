#ifndef BOUNDARYNODE_H
#define BOUNDARYNODE_H

namespace MC{
class BoundaryNode
{
public:
    double x;
    double y;
    int index;

    BoundaryNode();
    BoundaryNode(int index, double x, double y);
};
}

#endif // BOUNDARYNODE_H
