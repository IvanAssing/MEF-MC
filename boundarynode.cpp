#include "boundarynode.h"

MC::BoundaryNode::BoundaryNode()
{
}


MC::BoundaryNode::BoundaryNode(int index, double x, double y)
    :index(index), x(x), y(y)
{

}

void MC::BoundaryNode::draw(void)
{
    glBegin(GL_POINTS);
    {
        glVertex2d(x,y);
    }
    glEnd();
}
