
#include "roadmap.hpp"

Roadmap::Roadmap(PointGrid gd, double max_dist) {
    this->gd = gd;
    this->max_dist = max_dist;
}

Roadmap::~Roadmap() {

}

void Roadmap::insert(Point sample) {
    this->gd.insert(sample);
    std::list<Point> closest = this->gd.get_nearest(sample);
    std::list<Point>::const_iterator iterator;
    for (iterator = closest.begin(); iterator != closest.end(); ++iterator) {
        if (sample == *iterator) {
            continue;
        }

        if (sample.euclid_dist(*iterator) <= this->max_dist) {
            this->add_edge(sample, *iterator);
        }
    }
}

std::set<std::string> Roadmap::get_nodes() {
    return this->nodes;
}

Point Roadmap::decode(std::string p_str) {
    return this->decoder[p_str];
}

std::set<std::string> Roadmap::get_neighbours(Point p) {
    return this->get_neighbours(p.str());
}

std::set<std::string> Roadmap::get_neighbours(std::string p_str) {
    return this->edges[p_str];
}

void Roadmap::add_edge(Point p, Point q) {
    this->decoder[p.str()] = p;
    this->decoder[q.str()] = q;
    this->edges[p.str()].insert(q.str());
    this->edges[q.str()].insert(p.str());
    this->nodes.insert(p.str());
    this->nodes.insert(q.str());
}
