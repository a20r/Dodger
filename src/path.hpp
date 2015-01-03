
#ifndef PATH_H
#define PATH_H

#include <list>

class Path {

    public:
        Path(std::list<STPoint> st_list);
        ~Path();
        double get_max_time();
        Point get_position(double t);

    private:
        std::list<STPoint> st_list;
};

#endif
