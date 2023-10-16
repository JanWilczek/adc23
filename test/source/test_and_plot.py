import os
import sys
from pathlib import Path
import matplotlib.pyplot as plt
import soundfile as sf


def main():
    current_dir_path = Path(os.path.dirname(os.path.abspath(sys.argv[0])))
    root_repo_path = current_dir_path.parents[1]
    print(str(root_repo_path))
    test_executable_path = Path('build') / 'test' / 'Debug' / 'ExamplesTest.exe'
    ret = os.system(f'cd {root_repo_path} && cmake -S . -B build && cmake --build build && {test_executable_path} --gtest_filter="OutputTest.*"')

    data, fs = sf.read(root_repo_path / 'sine.wav')

    plt.figure()
    plt.plot(data)
    plt.show()


if __name__ == '__main__':
    main()
