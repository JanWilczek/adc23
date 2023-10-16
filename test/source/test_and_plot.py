import os
import sys
from pathlib import Path


def main():
    current_dir_path = Path(os.path.dirname(os.path.abspath(sys.argv[0])))
    root_repo_path = current_dir_path / '..' / '..'
    print(str(root_repo_path))
    ret = os.system(f'cd {root_repo_path} && cmake -S . -B build && cmake --build build && .\\build\\test\Debug\ExamplesTest.exe --gtest_filter="OutputTest.*"')


if __name__ == '__main__':
    main()
