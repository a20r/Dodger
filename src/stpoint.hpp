
#include "point.hpp"

class STPoint : public Point {

    public:
        STPoint(double x, double y, double z, double t);
        STPoint(double x, double y, double t);
        ~STPoint();
        double get_t();
        void set_t(double t);
        double st_dist(STPoint *other_point);

    protected:
        double t;

};
