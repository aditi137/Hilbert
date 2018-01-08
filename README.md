# Derivative-free Global Optimization Using Space-filling Curves
## Hilbert Curve
C++ implementation of Space-filling curve ...
- based on: [John Skilling] [link]
- [insert algo/psuedo code]
- explanation for wrapper usage

## Requirements

## Setup
MS Visual Studio (2013 and above) settings:
1. Go to `Project > Hilbert Properties... > Configuration Properties`. With All Configurations:
   - Chose VC++ Directories setting. Append `$(PYTHONPATH)\include` to Include Directories for the Python header file                  `<Python.h>` and append `$(PYTHONPATH)\libs` to Library Directories for the linker library file `pythonXX.lib` or `pythonXX_d.lib`.
   - Choose General settings and in Project Defaults, change Configuration Type to 'Dynamic Library (.dll)'.
   - Under General settings, change Target Extension to '.pyd'. 
   <br /><br />
   Only for Debug Configuration:
   - Under General settings, change Target Name to `$(ProjectName)_d`.

2. Chose either Release or Debug under Solution Configurations. Note that for Debug mode, you need to have Python debug binaries downloaded first (requires VS 2015 or later).

## Run
1. With Release configuration, Build Visual Studio project.
   <br />
   From CMD, run `dir Hilbert\Release` to locate `Hilbert.pyd` file.
   <br />
   Example commands in `test.py`.
   ```Shell
   cd Hilbert\Hilbert
   python test.py
   ```
2. For Debug mode, steps are similar as above. `Hilbert_d.pyd` file will be created under `Hilbert\Debug` and you may use the `pythonXX_d.exe` interpreter instead.
3. [how to call/use wrapper]

## Project Structure
Main project files:
```
Hilbert\Hilbert
|
|- Header Files
|		|
|		|- capi.h
|		|- hilbert.h
|
|- Python Scripts
|		|
|		|- test.py
|
|- Source Files
		|
		|- hilbert.cpp
		|- main.cpp
```
[file contents gist]
Uses the Python-C API

NOTE: README in progress.
