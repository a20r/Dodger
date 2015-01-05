
import math
import point


class Agent(object):

    def __init__(self, model_x, model_y):
        self.model_x = model_x
        self.model_y = model_y
        self.delta_t = 0.01
        self.r = 1.5
        self.k = 1.0

    def get_normal_dist(self, X, std):
        coeff = 1.0 / (std * math.sqrt(2.0 * math.pi))
        ret_val = coeff * math.exp(-math.pow(X, 2) / (2.0 * math.pow(std, 2)))
        return ret_val

    def get_position(self, t_0):
        return point.Point(self.model_x(t_0), self.model_y(t_0))

    def get_probability(self, x, y, t_0, t_m):
        assert t_0 < t_m
        t = t_0
        prob_sum = 0.0
        num_samples = 0

        while t <= t_m:
            num_samples += 1
            pos = self.get_position(t)
            dist = pos.dist_to(point.Point(x, y))
            prob = self.get_normal_dist(dist, self.k * (t - t_0) + 0.1)
            prob_sum += math.pow(t_m - t + 1, self.r) * prob
            t += self.delta_t

        return prob_sum / num_samples

    def get_pdf(self, t_0, t_m):
        assert t_0 < t_m
        return lambda x, y: self.get_probability(x, y, t_0, t_m)


def get_probability(x, y, t_0, t_m, *agents):
    assert len(agents) > 0
    assert t_0 < t_m
    sum_prob = 0.0
    for a in agents:
        sum_prob += a.get_probability(x, y, t_0, t_m)

    return sum_prob / len(agents)


def get_pdf(t_0, t_m, *agents):
    assert len(agents) > 0
    assert t_0 < t_m
    a_list = list()
    for a in agents:
        a_list.append(a.get_pdf(t_0, t_m))

    def __get_pdf(x, y):
        sum_prob = 0.0
        for pdf in a_list:
            sum_prob += pdf(x, y)

        return sum_prob / len(agents)

    return __get_pdf
