#include "boundaryintersection.h"

MC::BoundaryIntersection::BoundaryIntersection()
{
}

MC::BoundaryIntersection::BoundaryIntersection(BoundaryElement *element, double ksi, int edge)
    :element(element), ksi(ksi), edge(edge)
{

}
