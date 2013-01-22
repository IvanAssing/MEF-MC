#ifndef NODE_H
#define NODE_H

namespace MC{
class Node
{
public:
    double x;
    double y;
    int index;

    Node();
    Node(int index, double x, double y);
};
}

#endif // NODE_H
