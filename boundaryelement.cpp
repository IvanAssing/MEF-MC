#include "boundaryelement.h"

MC::BoundaryElement::BoundaryElement()
{
}


MC::BoundaryElement::BoundaryElement(MC::BoundaryNode *node1, MC::BoundaryNode *node2, MC::BoundaryNode *node3)
{
    nodes = new BoundaryNode*[N_NODES_BOUNDARY_ELEMENT];

    nodes[0] = node1;
    nodes[1] = node2;
    nodes[2] = node3;

    double *coef = new double[3];

    coef[0] = nodes[1]->x;
    coef[1] = 0.5*(nodes[2]->x-nodes[0]->x);
    coef[2] = 0.5*(nodes[2]->x+nodes[0]->x)-nodes[1]->x;

    curveX = Polynomial1D(2, coef);

    coef[0] = nodes[1]->y;
    coef[1] = 0.5*(nodes[2]->y-nodes[0]->y);
    coef[2] = 0.5*(nodes[2]->y+nodes[0]->y)-nodes[1]->y;

    curveY = Polynomial1D(2, coef);
}

void MC::BoundaryElement::draw(void)
{
    glColor4d(1.0, 1.0, 0.0, 1.0);
    glLineWidth(2.0f);

    double deltat = 0.1;

    glBegin(GL_LINES);
    {
        for(int i=0; i<20; i++){
            double t = -1.0+i*deltat;
            glVertex3d(curveX(t), curveY(t), 0.0);
            glVertex3d(curveX(t+deltat), curveY(t+deltat), 0.0);
        }
    }
    glEnd();
}
