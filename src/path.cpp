
#include <iterator>
#include "stpoint.hpp"
#include "path.hpp"

Path::Path(std::list<STPoint> st_list) {
    this->st_list = st_list;
}

Path::~Path() {

}

double Path::get_max_time() {
    return this->st_list.back().get_t();
}

Point Path::get_position(double t) {
    int i = 0;
    double t_diff, rel_t, x_vel, y_vel, x_pos, y_pos;
    std::list<STPoint>::const_iterator iterator;
    STPoint p, prev;
    for (iterator = this->st_list.begin();
            iterator != this->st_list.end(); ++iterator) {
        if (i == 0) {
            prev = *iterator;
            continue;
        }

        p = *iterator;

        if (t <= p.get_t()) {
            t_diff = p.get_t();
            rel_t = t - prev.get_t();
            x_vel = (p.get_x() - prev.get_x()) / t_diff;
            y_vel = (p.get_y() - prev.get_y()) / t_diff;
            x_pos = prev.get_x() + rel_t * x_vel;
            y_pos = prev.get_y() + rel_t * y_vel;
            Point ret_p(x_pos, y_pos);
            return ret_p;
        }

        i++;
    }


}
