# DAG Project: Graph Properties and PageRank

A small C++17 command-line application for analysing directed graphs. The program reads a graph from a CSV file, checks whether it is a directed acyclic graph (DAG), reports degree statistics, and calculates approximate PageRank values.

The project includes a POSIX shell launcher, so the normal way to build and run it is:

```bash
./graph_solution path/to/graph.txt
```

> Although the input is called `graph.txt` in the command above, each non-empty input line must use the comma-separated format described below. Files with a `.csv` extension are also supported.

## Features

- Parses directed edges from a text/CSV file.
- Represents the graph with an adjacency list.
- Detects cycles with **Kahn's topological-sort algorithm**.
- Computes the maximum in-degree and maximum out-degree.
- Computes PageRank with power iteration, damping, and dangling-node handling.
- Prints a concise summary to standard output.
- Appends the same summary to an output file in `test_cases/`.
- Skips malformed records with a warning instead of terminating the entire run.

## Requirements

The project is intended for Unix-like systems (Linux, macOS, and other POSIX environments) and requires:

- Bash or another shell compatible with the launcher script
- GNU Make
- `g++` with C++17 support

On Debian or Ubuntu, the compiler and build tools can be installed with:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

On Fedora, the equivalent package group is:

```bash
sudo dnf group install "Development Tools"
```

## Input format

The input file contains one directed edge per non-empty line:

```text
source,target
```

`source` and `target` must be signed 64-bit integer node identifiers. Whitespace is not removed explicitly, although numeric conversion accepts whitespace around the values. A node is included in the graph even when it only appears as the target of an edge.

Example input:

```text
1,2
1,3
2,4
3,4
```

This describes the edges `1 → 2`, `1 → 3`, `2 → 4`, and `3 → 4`.

Blank lines are ignored. Lines without a comma, lines with non-numeric identifiers, and other malformed records are skipped and produce a warning on standard error. Multiple identical edges are retained as separate edges and therefore contribute separately to degree counts and PageRank transitions.

## Build and run

From the project root, make the launcher executable if necessary, then run it with the input path:

```bash
chmod +x graph_solution
./graph_solution path/to/graph.txt
```

The launcher:

1. Verifies that `make` and `g++` are available.
2. Runs `make` to compile the current sources.
3. Executes the generated `build/bin` binary.

The launcher changes to the project directory before building and executing, so it can be invoked from another working directory using an absolute or relative path to the launcher. The input path is passed unchanged to the C++ program; use an absolute path or a path valid from the project directory when invoking it from elsewhere.

You can also build the binary directly:

```bash
make
./build/bin path/to/graph.txt
```

To remove generated object files, dependency files, and the built binary:

```bash
make clean
```

## Output

For a successful run, the program prints:

```text
Is DAG: true
Max Out-Degree: 2
Max In-Degree: 2
Max PageRank: 0.373456
Min PageRank: 0.134567
```

The PageRank values are displayed rounded to six decimal places. `Is DAG` is reported as `true` when every node can be processed by Kahn's algorithm; otherwise it is `false`.

The program also appends these five lines to an output file:

- Input names matching `graph<number>.csv` are written to `test_cases/graph<number>_output.txt`.
- Other input names are written to `test_cases/graph_output.txt`.

Because output files are opened in append mode, running the same input repeatedly adds another result block rather than replacing previous results. The destination directory must exist and be writable. An input file that cannot be opened produces an error, but the current program continues and reports metrics for the graph data loaded up to that point (which may be empty).

## Algorithms and implementation details

### DAG detection

`Graph::isDag()` calculates all in-degrees, queues nodes with zero in-degree, and repeatedly removes them while decrementing their neighbours' in-degrees. If every known node is processed, the graph is acyclic; otherwise, at least one cycle remains.

### Degree metrics

- **Maximum out-degree** is the largest adjacency-list size among all nodes.
- **Maximum in-degree** is the largest number of incoming edges for any node.
- An empty graph returns zero for both metrics.

### PageRank

`PageRank::pageRankScore()` uses a damping factor of `0.85`, starts every node with equal rank, and performs 20 power-iteration steps. Dangling nodes (nodes with no outgoing edges) distribute their rank uniformly across all nodes. The minimum and maximum scores are rounded to six decimal places when reported.

## Project layout

```text
.
├── graph_solution       # POSIX launcher: builds and runs the application
├── Makefile             # C++17 build rules
├── README.md
├── src/
│   ├── graph.h          # Graph interface
│   ├── graph.cpp        # CSV parsing, degrees, and DAG detection
│   ├── PageRank.h       # PageRank interface
│   ├── PageRank.cpp     # PageRank calculation
│   └── main.cpp         # Command-line entry point and output handling
└── test_cases/
    ├── graph*.csv       # Sample graph inputs
    └── graph*_output.txt # Sample/generated output summaries
```

Build artifacts are placed under `build/` and are ignored by Git.

## Testing with the included graphs

The repository contains sample graphs that can be run from the project root:

```bash
./graph_solution test_cases/graph1.csv
./graph_solution test_cases/graph2.csv
./graph_solution test_cases/graph3.csv
```

Their expected summary formats are recorded in the corresponding files under `test_cases/`. Since those files are append-only outputs, compare a newly captured run separately if you need a clean test result.

## License

MIT
