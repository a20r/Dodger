
#ifndef PATH_H
#define PATH_H

#include <list>
#include "stpoint.hpp"

class Path {

    public:
        Path() {};
        Path(std::list<STPoint> st_list, double cost);
        ~Path() {};
        double get_max_time();
        double get_cost();
        Point get_position(double t);
        std::list<STPoint> get_list();
        std::string json();
        void write_json(std::string filename);

    private:
        std::list<STPoint> st_list;
        double cost;
};

#endif
