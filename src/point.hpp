
class Point {

    public:
        Point(double x, double y);
        ~Point();
        double get_x();
        double get_y();
        void set_x(double x);
        void set_y(double y);
        double euclid_dist(Point* other_point);
        Point* to_unit_vector();

    private:
        int x;
        int y;

};
