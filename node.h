#ifndef NODE_H
#define NODE_H

namespace MC
{
    class Node
    {
        public:
            int index;
            double x;
            double y;


            Node();
            Node(int index, double x, double y);
    };
}

#endif // NODE_H
