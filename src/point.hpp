
class Point {

    public:
        Point();
        Point(double x, double y);
        Point(double x, double y, double z);
        ~Point();
        double get_x();
        double get_y();
        double get_z();
        void set_x(double x);
        void set_y(double y);
        void set_z(double y);
        double euclid_dist(Point *other_point);
        Point *to_unit_vector();
        static Point *get_random_point_2d(double width, double height);

    protected:
        double x;
        double y;
        double z;

};
