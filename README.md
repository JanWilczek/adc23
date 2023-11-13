# Companion Repo for my Audio Developer Conference 2023 Talk

## "Bug-Free Audio Code: Leverage Simple DSP Principles To Write Rock-Solid Music Software Every Time"

### by Jan Wilczek from TheWolfSound.com

![thumbnail](img/Bug-free%20audio%20code-_Title%20Card%20copy.png)

### TODO:

1. Thumbnail
1. Link to the course
1. Link to the slides
1. Link to audio plugin template
1. Disclaimer on code quality and contributions
1. License

## C++ Setup (Cross-Platform)

After cloning this repo locally, you can proceed with the usual CMake workflow.

In the main repo directory execute

```powershell
> cmake -S . -B build
> cmake --build build
```

The first run will take the most time because the dependencies need to be downloaded.

You can now run the unit tests from the command line using `ctest`

```powershell
> cd build
> ctest
```

or one of the Python tests

```powershell
> python test/source/test_and_plot.py
```

## Python Setup (Windows)

In the main repo run

```powershell
> python -m venv WORK
> WORK\Scripts\activate.bat
(WORK) > "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
(WORK) > python -m pip install cppyy numpy matplotlib
```

You can now run

```powershell
(WORK) > python test/source/gain_test.py
```
