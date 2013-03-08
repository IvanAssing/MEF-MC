#include "edgesegment.h"

MC::EdgeSegment::EdgeSegment()
{
}

MC::EdgeSegment::EdgeSegment(double x0, double y0, double x1, double y1)
{
}


void MC::EdgeSegment::setLinks(EdgeSegment *previous_, EdgeSegment *next_)
{
    prev = previous_;
    next = next_;
}
