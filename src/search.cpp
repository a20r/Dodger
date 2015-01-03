
#include "search.hpp"

Search::Search(Roadmap rm, double speed, double wait_time) {
    this->rm = rm;
    this->speed = speed;
    this->wait_time = wait_time;
}

double Search::get_cost(STPoint n1, STPoint n2, std::list<Agent> agents) {

}

std::list<STPoint> Search::get_st_neighbours(STPoint node) {

}

Path Search::get_path(Point s_pt, Point e_pt, std::list<Agent> agents) {

}

Path Search::backtrack_path(std::map<std::string, std::string> parents,
        std::string goal) {

}
