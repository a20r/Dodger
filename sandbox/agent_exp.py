
import math
import matplotlib.pyplot as plt
import random
from mpl_toolkits.mplot3d import Axes3D


max_x = 4
max_y = 4

s_x = 2
s_y = 2

last_x = s_x
last_y = s_y

delta_t = 0.1
max_time = 7

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

ax.set_xlim(0, max_x)
ax.set_ylim(0, max_y)

tau = 0.01


def zeta_x_prime(t):
    return 4 * math.cos(2 * t)


def zeta_y_prime(t):
    return 0


def zeta_x(t):
    global last_x

    if t == 0:
        return s_x

    ret_val = last_x + zeta_x_prime(t) * delta_t + random.gauss(0, 0.1)
    last_x = ret_val
    return ret_val


def zeta_y(t):
    global last_y

    if t == 0:
        return s_y

    ret_val = last_y + zeta_y_prime(t) * delta_t + random.gauss(0, 0.1)
    last_y = ret_val
    return ret_val


def _zeta_x(t):
    return 2 * math.sin(2 * t) + 2 + random.gauss(0, tau * t)


def _zeta_y(t):
    return 2 + random.gauss(0, tau * t)


def run():
    t = 0
    xs = list()
    ys = list()
    ts = list()
    while t < max_time:
        xs.append(zeta_x(t))
        ys.append(zeta_y(t))
        ts.append(t)
        t += delta_t

    ax.plot(xs, ys, ts)
    plt.show()


if __name__ == "__main__":
    run()
