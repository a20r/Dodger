
struct Pair {
    int i, j;
};

class PointGrid {

    public:
        PointGrid(const int width, const int height,
                double a_width, double a_height);
        ~PointGrid();
        void insert(Point *p);
        struct Pair transform(Point *p);
        std::list<Point *> get(int i, int j);
        std::list<Point *> get_nearest(Point *p);

    private:
        int map_val(double x, double in_min, double in_max,
                int out_min, int out_max);
        int width;
        int height;
        double a_width;
        double a_height;
        std::vector<std::vector<std::list<Point *>>> grid;
};
