
#include <iostream>
#include <sstream>
#include <iterator>
#include "stpoint.hpp"
#include "path.hpp"

namespace Dodger {

    Path::Path(vector<STPoint> st_list, double cost) {
        this->st_list = st_list;
        this->cost = cost;
    }

    Path::Path(vector<STPoint> st_list) {
        this->st_list = st_list;
        this->cost = 0;
    }

    double Path::get_max_time() {
        return this->st_list.back().get_t();
    }

    Point Path::get_position(double t) {
        double t_diff, rel_t, x_vel, y_vel, x_pos, y_pos;
        STPoint p, prev;
        for (int i = 0; i < this->st_list.size() - 1; i++) {
            p = st_list[i + 1];
            prev = st_list[i];
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
        }
    }

    STPoint Path::get(int i) {
        return this->st_list[i];
    }

    vector<STPoint> Path::get_list() {
        return this->st_list;
    }

    double Path::get_cost() {
        return this->cost;
    }

    std::string Path::json() {
        std::stringstream buffer;
        buffer << "[";
        int i = 0;
        for (STPoint stp : this->st_list) {
            buffer << stp.json();
            if (i++ < st_list.size() - 1) {
                buffer << ",";
            }
        }

        buffer << "]";
        return buffer.str();
    }

    void Path::write_json(std::string filename) {

    }
}
