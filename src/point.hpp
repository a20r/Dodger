
#ifndef POINT_H
#define POINT_H

#include <string>

namespace Dodger {

    class Point {

        public:
            Point() {};
            Point(double x, double y);
            Point(double x, double y, double z);
            ~Point();
            double get_x() const;
            double get_y() const;
            double get_z() const;
            void set_x(double x);
            void set_y(double y);
            void set_z(double y);
            double euclid_dist(Point other_point);
            Point to_unit_vector();
            std::string str();
            bool operator==(Point rhs);
            static Point get_random_point_2d(double width, double height);

        protected:
            double x;
            double y;
            double z;

    };
}

#endif
