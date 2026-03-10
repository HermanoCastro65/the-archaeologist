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

## Docker Usage

The Archaeologist provides two Docker environments.

### 1. Build and Test Environment

This container performs a clean build and runs the test suite.

Build the image:

```bash
docker build -f docker/Dockerfile.tests -t archaeologist-tests .
```

Run the container:

```bash
docker run --rm archaeologist-tests
```
Docker will:

1. Build the C++ engine

2. Run the test suite

3. Validate the project in a clean Linux environment


### 2. Python UI Container (Headless)

This container builds the C++ engine and runs the Python UI inside a virtual display.

Build the image:

```bash
docker build -f docker/Dockerfile.ui -t archaeologist-ui .
```

Run the container:

```bash
docker run -it archaeologist-ui
```
The UI runs inside a virtual display (Xvfb), so the Tkinter window will not appear on the host machine.
This mode is mainly useful for containerized environments and CI testing.

## Build and Launch the UI Locally

You can build the project and run the UI directly on the host machine.

Run the build script:

```bash
chmod +x scripts/build.sh
./scripts/build.sh
```

This will:

1. Build the C++ engine

2. Compile the Python bindings

3. Run the test suite

After the build finishes, launch the Python UI:

```bash
python archaeologist_ui/main.py
```

---

# Using the Interface

The UI provides two buttons:

*SELF RUNNER*

Scans the Archaeologist project itself.

*RUN THE ARCHAEOLOGIST*

Allows selecting any directory to scan.

A project report and directory tree will appear in the terminal panel.

*SCAN GIT REPO*

Scans a project directory or a remote Git repository.

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