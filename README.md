# The Archaeologist

A tool for exploring and understanding large codebases.

The Archaeologist scans a project directory, builds a hierarchical view of the codebase, and generates a report of file types to help developers quickly understand the structure of unfamiliar repositories.

It includes a C++ scanning engine and a Python graphical interface.

---

# Features

- Project structure analysis
- Directory tree visualization
- File type statistics
- Self-analysis mode (scan its own repository)
- Scan any external project
- Python Matrix-style terminal UI
- CLI support

---

# How it works

The project consists of two parts:

### C++ Core
Responsible for:

- scanning directories
- building the project tree
- generating reports
- running the analysis engine

### Python UI
Provides:

- interactive interface
- animated terminal output
- project selection dialog
- responsive window interface

The Python UI communicates with the C++ engine through **pybind11 bindings**.

---

# Running The Archaeologist

## Build and launch the UI

```bash
chmod +x build.sh
./build.sh
```

This will:
1. Build the C++ engine
2. Compile the Python bindings
3. Run the test suite
4. Launch the graphical interface

---

# Using the Interface

The UI provides two buttons:

*SELF RUNNER*

Scans the Archaeologist project itself.

*RUN THE ARCHAEOLOGIST*

Allows selecting any directory to scan.

A project report and directory tree will appear in the terminal panel.

---

# CLI Usage

You can also run the scanner directly from the command line:

```bash
./build/the_archaeologist <path>
```
Example:

```bash
./build/the_archaeologist .
./build/the_archaeologist ../my_project
```
---
# Example Output

```bash
Running Archaeologist self-runner...
Scanning project: .

.
|-- src
|-- include
|-- tests

Project Report
==============

Total files: 27

File types
----------
.cpp : 14
.h   : 4
.py  : 2
.md  : 1
```
---

# Project Structure
```bash
the-archaeologist
├── bindings
├── include
├── python
├── src
├── tests
├── build.sh
└── CMakeLists.txt
```
---

# Future Improvements

* Planned improvements include:
* interactive directory tree viewer
* dependency graphs
* code metrics analysis
* TUI mode
* global CLI installation
* plugin system
---

# License
MIT License