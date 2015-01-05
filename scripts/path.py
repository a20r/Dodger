
import point


class Path(list):

    def get_max_time(self):
        return self[-1].t

    def __call__(self, t):
        for i, p in enumerate(self):
            if i == 0:
                continue

            if t <= p.get_t():
                t_diff = p.t - self[i - 1].t
                rel_t = float(t) - self[i - 1].t
                x_vel = (p.x - self[i - 1].x) / t_diff
                y_vel = (p.y - self[i - 1].y) / t_diff
                x_pos = self[i - 1].x + rel_t * x_vel
                y_pos = self[i - 1].y + rel_t * y_vel
                return point.Point(x_pos, y_pos)


def make(*args):
    return Path(*args)
