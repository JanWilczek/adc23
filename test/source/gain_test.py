import cppyy
from cppyy.gbl import std
import numpy as np
import matplotlib.pyplot as plt
import os
import sys


def main():
    cppyy.add_include_path(os.path.dirname(os.path.abspath(sys.argv[0])))
    cppyy.include("gain.h")
    ones = np.ones((10,))

    ones_vector = std.vector[float](ones.tolist())
    cppyy.gbl.apply_gain(ones_vector)

    plt.plot(ones_vector)
    plt.show()


if __name__ == '__main__':
    main()
