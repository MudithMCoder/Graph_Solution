# DAG Project: Graph Properties + PageRank (C++)

A C++ application to parse directed graphs from CSV files, determine whether the graph is a DAG (via **Kahn’s algorithm**), compute **in/out degree** statistics, and calculate **PageRank** scores.

---

## Features

- **CSV graph ingestion**: reads directed edges from `source,target` lines.
- **DAG detection**: cycle check using **Kahn’s algorithm**.
- **Degree metrics**: maximum in-degree and maximum out-degree.
- **PageRank**: power-iteration PageRank with handling for dangling nodes.

---

## Input Format

CSV file where each non-empty line contains a directed edge:

```
source,target
```

Example:

```
1,2
1,3
2,4
```

---

## Build

Requires a C++17-compatible compiler.

```bash
make
```

The binary will be built at:

- `build/bin`

---

## Run

```bash
./build/bin <path_to_graph_csv>
```

The program prints:

- `Is DAG: true|false`
- `Max Out-Degree: <value>`
- `Max In-Degree: <value>`
- `Max PageRank: <value>`
- `Min PageRank: <value>`

It also appends these results to a test output file under `test_cases/`.

---

## Project Structure

- `src/graph.h`, `src/graph.cpp`
  - Graph storage (adjacency list), DAG check, degree calculations.
- `src/PageRank.h`, `src/PageRank.cpp`
  - PageRank score computation and min/max reporting.
- `src/main.cpp`
  - CLI entrypoint, file parsing, and output formatting.

---

## Notes

- Malformed CSV lines are skipped with a warning.
- PageRank uses a fixed number of iterations for score approximation.

---

## License

MIT
