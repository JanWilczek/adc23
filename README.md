# Companion Repo for my Audio Developer Conference 2023 Talk

## "Bug-Free Audio Code: Leverage Simple DSP Principles To Write Rock-Solid Music Software Every Time"

### by Jan Wilczek from TheWolfSound.com

![thumbnail](img/Bug-free%20audio%20code-_Title%20Card%20copy.png)

## Important links

[Slides](Slides.pdf)

[DSP Pro Online Course](https://wolfsoundacademy.com/dsp-pro): Your structured learning path of digital audio signal processing from a complete beginner to a well-versed professional

[Audio plugin template](https://github.com/JanWilczek/audio-plugin-template): A template repo with JUCE, CMake and CPM package manager set up, including unit tests of your audio processor (I use it for all my audio projects, also this repo)

## Disclaimer

This repo contains example code which is **not** reference code; the included examples are meant to illustrate certain concepts and are not necessarily what I consider clean code. At the same time, it is code that you may encounter in various codebases so these examples are "real-world".

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
