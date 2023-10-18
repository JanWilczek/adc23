import cppyy
from cppyy.gbl import std
import numpy as np
import matplotlib.pyplot as plt
import os
import sys


def apply_gain(samples):
    samples *= 0.5


def generate_reference():
    ones = np.ones((10,))

    apply_gain(ones)

    # save output
    # ...
    plt.figure()
    plt.plot(ones)


def test_cpp():
    cppyy.add_include_path(os.path.dirname(os.path.abspath(sys.argv[0])))
    cppyy.include("gain.h")
    ones = np.ones((10,))

    ones_vector = std.vector[float](ones.tolist())

    # call C++ implementation
    cppyy.gbl.apply_gain(ones_vector)

    # test against saved output
    # ...
    plt.figure()
    plt.plot(ones_vector)


def main():
    generate_reference()
    test_cpp()
    plt.show()


if __name__ == '__main__':
    main()
