import os
import sys
from pathlib import Path
import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np


def main():
    current_dir_path = Path(os.path.dirname(os.path.abspath(sys.argv[0])))
    root_repo_path = current_dir_path.parents[1]
    print(str(root_repo_path))
    test_executable_path = Path('build') / 'test' / 'Debug' / 'ExamplesTest.exe'
    ret = os.system(f'cd {root_repo_path} && cmake -S . -B build && cmake --build build &&'
                    f' {test_executable_path} --gtest_filter="OutputTest.*"')

    data, fs = sf.read(root_repo_path / 'sine.wav')

    plt.figure()
    plt.plot(data)

    dft_data = np.loadtxt(root_repo_path / "dft_data.csv", delimiter=";", skiprows=1)

    plt.figure()
    plt.stem(dft_data[:, 0], dft_data[:, 1])

    data, fs = sf.read(root_repo_path / 'audio_player_output.wav')
    assert data.shape[1] == 2

    plt.figure()
    plt.subplot(211)
    plt.plot(data[:, 0])
    plt.subplot(212)
    plt.plot(data[:, 1])
    plt.show()


if __name__ == '__main__':
    main()
