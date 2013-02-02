#include "elementedge.h"

MC::ElementEdge::ElementEdge()
{
}

MC::ElementEdge::ElementEdge(int indexH1_, int indexH2_, int indexV1_, int indexV2_,
                             BoundaryElement *element_, double ksi_)
    :indexH1(indexH1_), indexH2(indexH2_), indexV1(indexV1_), indexV2(indexV2_),
      element(element_), ksi(ksi_)
{

}

void MC::ElementEdge::draw(void)
{
    double dh = 1.0;

    glLineWidth(8.f);
    glColor4f(1.0f, 0.0f, 0.0f, 1.5f);

    if(indexH1 == indexH2){
        glBegin(GL_LINES);
        glVertex2d(element->curveX(ksi)-dh, element->curveY(ksi));
        glVertex2d(element->curveX(ksi)+dh, element->curveY(ksi));
        glEnd();
    }
    else{
        glBegin(GL_LINES);
        glVertex2d(element->curveX(ksi), element->curveY(ksi)-dh);
        glVertex2d(element->curveX(ksi), element->curveY(ksi)+dh);
        glEnd();
    }
    glPointSize(8.f);
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2d(element->curveX(ksi), element->curveY(ksi));
    glEnd();
}
