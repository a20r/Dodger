
#ifndef STPOINT_H
#define STPOINT_H

#include "point.hpp"

class STPoint : public Point {

    public:
        STPoint() {};
        STPoint(double x, double y, double t);
        STPoint(double x, double y, double z, double t);
        ~STPoint() {};
        double get_t() const;
        void set_t(double t);
        double st_dist(STPoint *other_point);

    protected:
        double t;

};

class STPointWeight {

    public:
        STPointWeight() {};
        STPointWeight(STPoint val, double weight);
        STPoint get_val();
        double get_weight();
        bool operator<(STPointWeight& right);

    private:
        STPoint val;
        double weight;

};


#endif
