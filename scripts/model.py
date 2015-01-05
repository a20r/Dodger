
import math


class Model(object):

    def __call__(self, t):
        return t


class LinearModel(Model):

    @staticmethod
    def get_number_of_arguments():
        return 2

    def __init__(self, m, b):
        self.m = m
        self.b = b

    def __call__(self, t):
        return self.m * t + self.b


class SinModel(Model):

    @staticmethod
    def get_number_of_arguments():
        return 4

    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def __call__(self, t):
        return self.a * math.sin(self.b * t + self.c) + self.d


class ExpModel(Model):

    @staticmethod
    def get_number_of_arguments():
        return 4

    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def __call__(self, t):
        return self.a * math.exp(self.b * t + self.c) + self.d


def get_model_list():
    return [LinearModel, SinModel, ExpModel]


models = {
    "Linear": LinearModel,
    "Sin": SinModel
}
