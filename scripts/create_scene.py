
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import math


def norm_scaled(x, mu, sigma):
    return math.exp(-0.5 * math.pow((x - mu) / sigma, 2))


def dist(a, b):
    ad1 = math.pow(a[0] - b[0], 2)
    ad2 = math.pow(a[1] - b[1], 2)
    return math.sqrt(ad1 + ad2)


def create_gaussian(pos_list, dim, sigma):
    space = np.zeros((dim, dim))
    for x in xrange(dim):
        for y in xrange(dim):
            val = 0
            for pos in pos_list:
                d_val = dist(pos, [x, y])
                g_val = norm_scaled(d_val, 0, sigma)
                if g_val > val:
                    val = g_val
            space[x, y] = val
    return space


if __name__ == "__main__":
    dim = 100
    space = create_gaussian([[dim / 2, dim / 2]], dim, 20)
    plt.pcolormesh(space, cmap=cm.jet, shading="gouraud")
    plt.axis("off")
    plt.savefig("figures/normal_3d.pdf", bbox_inches="tight")
    plt.show()
