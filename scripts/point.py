
import math
import stpoint
import random


class Point(object):

    def __init__(self, x, y, z=0):
        self.x = x
        self.y = y
        self.z = z

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_z(self):
        return self.z

    def set_x(self, x):
        self.x = x
        return self

    def set_y(self, y):
        self.y = y
        return self

    def set_z(self, z):
        self.z = z
        return self

    def dist_to(self, other_point):
        return math.sqrt(
            pow(self.x - other_point.x, 2) +
            pow(self.y - other_point.y, 2) +
            pow(self.z - other_point.z, 2)
        )

    def to_unit_vector(self):
        mag = self.dist_to(Point(0, 0, 0))

        if mag == 0:
            return Point(0, 0, 0)
        else:
            return Point(self.x / mag, self.y / mag, self.z / mag)

    def to_st_point_2d(self, t):
        return stpoint.make(self.x, self.y, t)

    def to_list(self):
        return [self.x, self.y, self.z]

    def __str__(self):
        return "X: {0}, Y: {1}, Z: {2}".format(self.x, self.y, self.z)

    def __repr__(self):
        return "Point({0}, {1}, {2})".format(self.x, self.y, self.z)

    def __hash__(self):
        return hash(str(self))

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y, self.z + other.z)

    def __mult__(self, scalar):
        return Point(scalar * self.x, scalar * self.y, scalar * self.z)

    def __eq__(self, val):
        try:
            return val.x == self.x and val.y == self.y and val.z == self.z
        except:
            return False


def make(*args, **kwargs):
    return Point(*args, **kwargs)


def get_random_point(width, height):
    x = random.uniform(0, width)
    y = random.uniform(0, height)

    return Point(x, y)


def get_random_point_3d(width, height, altitude):
    p = get_random_point(width, height)
    p.set_z(random.randint(0, altitude))

    return p
