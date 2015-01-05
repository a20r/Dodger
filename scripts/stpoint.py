
import math
import util
import random
import point


class STPoint(object):

    def __init__(self, x, y, t):
        self.x = x
        self.y = y
        self.t = t

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_t(self):
        return self.t

    def within(self, x_min, x_max, y_min, y_max):
        x_in = self.x >= x_min and self.x < x_max
        y_in = self.y >= y_min and self.y < y_max
        return x_in and y_in

    def to_point(self):
        return point.make(self.x, self.y)

    @util.check_attrs(["x", "y"])
    def euclid_dist(self, other):
        pow_x = pow(self.x - other.x, 2)
        pow_y = pow(self.y - other.y, 2)
        return math.sqrt(pow_x + pow_y)

    @util.check_attrs(["x", "y", "t"])
    def st_dist(self, other):
        pow_x = pow(self.x - other.x, 2)
        pow_y = pow(self.y - other.y, 2)
        pow_t = pow(self.t - other.t, 2)
        return math.sqrt(pow_x + pow_y + pow_t)

    @util.check_attrs(["x", "y", "t"])
    def __sub__(self, other):
        d_x = self.x - other.x
        d_y = self.y - other.y
        d_t = self.t - other.t
        return STPoint(d_x, d_y, d_t)

    @util.check_attrs(["x", "y", "t"])
    def __add__(self, other):
        a_x = self.x + other.x
        a_y = self.y + other.y
        a_t = self.t + other.t
        return STPoint(a_x, a_y, a_t)

    def __str__(self):
        return "x --> {}, y --> {}, t --> {}".format(self.x, self.y, self.t)

    def __repr__(self):
        return "STPoint(x={}, y={}, t={})".format(self.x, self.y, self.t)

    def __hash__(self):
        return hash(str(self))

    @util.check_attrs(["x", "y", "t"])
    def __eq__(self, other):
        eq_x = abs(self.x - other.x) < 0.0001
        eq_y = abs(self.y - other.y) < 0.0001
        eq_t = abs(self.t - other.t) < 0.0001
        return eq_x and eq_y and eq_t


def make(x, y, t):
    return STPoint(x, y, t)


def get_random(x_range, y_range, t_range):
    rand_x = random.uniform(x_range[0], x_range[1])
    rand_y = random.uniform(y_range[0], y_range[1])
    rand_t = random.uniform(t_range[0], t_range[1])
    return STPoint(rand_x, rand_y, rand_t)


def get_sample(ref, radius, t_diff):
    rand_angle = 2 * math.pi * random.random()
    samp_rad = radius * random.random()
    x = samp_rad * math.cos(rand_angle)
    y = samp_rad * math.sin(rand_angle)
    t = ref.t + t_diff * (2 * math.random() - 1)
    return STPoint(x, y, t)
