#include "boundarynode.h"

MC::BoundaryNode::BoundaryNode()
{
}


MC::BoundaryNode::BoundaryNode(int index_, double x_, double y_)
    :index(index_), x(x_), y(y_)
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
