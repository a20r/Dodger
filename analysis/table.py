
import csv
import numpy as np


class Table(object):

    def __init__(self, headers):
        self.data = dict()
        self.rows = list()
        self.headers = map(lambda val: val.strip(), headers)
        print self.headers
        self.index_data = dict()
        for header in self.headers:
            self.data[header] = list()
            self.index_data[header] = dict()

    def get_headers(self):
        return self.headers

    def plot(self, h_x, h_y, plt, **kwargs):
        plt.scatter(self(h_x), self(h_y), **kwargs)
        plt.xlabel(h_x)
        plt.ylabel(h_y)

    def plot_func(self, h_x, h_y, func, plt, label=""):
        xs = np.linspace(min(self(h_x)), max(self(h_x)), 1000)
        ys = func(xs)
        plt.plot(xs, ys, lw=3, label=label)
        plt.xlabel(h_x)
        plt.ylabel(h_y)

    def splice(self, headers):
        ret_dict = dict()
        for header in headers:
            ret_dict[header] = self.data[header]
        return ret_dict

    def to_matrix(self, *headers):
        mat = [list() for _ in xrange(len(self.rows))]
        for header in headers:
            for j, datum in enumerate(self.data[header]):
                mat[j].append(datum)

        return mat

    def try_conv(self, elem):
        try:
            return float(elem)
        except ValueError:
            if elem == "NA":
                raise ValueError()
            else:
                return elem

    def get_num_rows(self):
        return len(self.rows)

    def add_row(self, row):
        try:
            row = map(self.try_conv, row)
        except ValueError:
            return self

        self.rows.append(row)
        for i, elem in enumerate(row):
            self.data[self.headers[i]].append(elem)
            if not elem in self.index_data[self.headers[i]].keys():
                self.index_data[self.headers[i]][elem] = dict()
                for header in self.headers:
                    self.index_data[self.headers[i]][elem][header] = list()
            for j, inner_elem in enumerate(row):
                self.index_data[self.headers[i]][elem][self.headers[j]]\
                    .append(inner_elem)

        return self

    def get_row(self, i):
        return self.rows[i]

    def __getitem__(self, index):
        ret_dict = dict()
        for i, header in enumerate(self.headers):
            ret_dict[header] = self.rows[index][i]
        return ret_dict

    def __call__(self, index, value=None, s_index=None):
        if value:
            if s_index:
                return self.index_data[index][value][s_index]
            else:
                return self.index_data[index][value]
        else:
            return self.data[index]


def load_csv(csv_filename):
    tab = None
    with open(csv_filename) as f:
        reader = csv.reader(f)
        for i, row in enumerate(reader):
            if i == 0:
                tab = Table(row)
            else:
                tab.add_row(row)
    return tab
