#ifndef EDGESEGMENT_H
#define EDGESEGMENT_H


namespace MC
{
    class EdgeSegment
    {
        public:
            EdgeSegment *prev, *next;


            EdgeSegment();
            EdgeSegment(double x0, double y0, double x1, double y1);

            void setLinks(EdgeSegment *previous, EdgeSegment *next);
    };
}

#endif // EDGESEGMENT_H
