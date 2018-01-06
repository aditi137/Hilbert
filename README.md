# Derivative-free Global Optimization Using Space-filling Curves
## Hilbert Curve
C++ implementation of []
- based on: [John Skilling] [insert link]
- [insert algo/psuedo code]

## Requirements

## Setup
MS Visual Studio (2013 and above) settings:
- Go to `Project > Hilbert Properties... > Configuration Properties`
<br />
With All Configurations:
<br />
- [ ] Chose VC++ Directories setting and append `$PYTHONPATH\include` to Include Directories for the Python header file `<Python.h>`.
- [ ] Chose VC++ Directories setting and append `$PYTHONPATH\libs` to Library Directories for the linker library file `pythonXX.lib` or `pythonXX_d.lib`.
- [ ] In General settings, change Target Extension to '.pyd'
<br />
Additionally for Debug Configuration:
- [ ] In General settings, change Target Name to `$(ProjectName)_d`
- Chose either Release or Debug under Solution Configurations. Note that for Debug mode, you need to have Python debug binaries downloaded first (requires VS 2015 or later).

## Run
With Release configuration, Build Visual Studio project.
<br />
From CMD, run `dir Hilbert\Release` to locate `Hilbert.pyd file`
<br />

Example commands:
```Shell
cd Hilbert	# Project Directory
set PYTHONPATH=Release\	# optional, to expose python Hilbert module globally
python Hilbert\test.py
```

For Debug mode, steps are similar as above. `Hilbert_d.pyd` file will be created under `Hilbert\Debug` and you may use the `pythonXX_d.exe` interpreter instead.
<br />
[how to call/use wrapper]

## Project Structure
Main project files:
```
Hilbert\Hilbert
|
|- Header Files
|		|- capi.h
|		|- hilbert.h
|
|- Python Scripts
|		|- test.py
|
|- Source Files
		|- hilbert.cpp
		|- main.cpp
```
[file contents gist]

NOTE: README in progress.