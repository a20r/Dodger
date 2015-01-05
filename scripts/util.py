
class check_attrs(object):

    def __init__(self, attrs):
        self.attrs = attrs

    def __call__(self, f):
        def __inner(*inputs):
            for ins in inputs:
                for attr in self.attrs:
                    if not hasattr(ins, attr):
                        raise AttributeError("{} does not have {}".format(
                            repr(ins), attr))
            return f(*inputs)

        return __inner
