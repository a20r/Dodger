
#ifndef PATH_H
#define PATH_H

#include <vector>
#include "stpoint.hpp"

using namespace std;

namespace Dodger {

    class Path {

        public:
            Path() {};
            Path(vector<STPoint> st_list, double cost);
            Path(vector<STPoint> st_list);
            ~Path() {};
            double get_max_time();
            double get_cost();
            STPoint get(int i);
            Point get_position(double t);
            vector<STPoint> get_list();
            string json();
            void write_json(string filename);

        private:
            vector<STPoint> st_list;
            double cost;
    };
}
#endif
