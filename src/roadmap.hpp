
#ifndef ROADMAP_H
#define ROADMAP_H

#include <map>
#include <set>
#include <list>
#include <string>
#include "point.hpp"
#include "grid.hpp"

class Roadmap {

    public:
        Roadmap() {};
        Roadmap(PointGrid gd, double max_dist);
        ~Roadmap();
        void insert(Point sample);
        std::set<std::string> get_nodes();
        std::set<std::string> get_neighbours(Point p);
        std::set<std::string> get_neighbours(std::string p_str);
        Point decode(std::string p_str);

    private:
        void add_edge(Point p, Point q);
        PointGrid gd;
        double max_dist;
        std::map<std::string, std::set<std::string>> edges;
        std::map<std::string, Point> decoder;
        std::set<std::string> nodes;
};

#endif
