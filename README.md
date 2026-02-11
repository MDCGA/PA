<div align="center">
  
# PA-Pathfinding algorithm benchmark platform

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

This is a benchmark platform for pathfinding algorithm targets running on the embeded devices. This platform contains 5 different algorithms (A*, BFS, DFS, Dijkstra and FA) written in C and Rust. Using Python and Makfile script to bench them.
</div>

## How to bench
```sh
# First, build all the binaries of these algorithms
make build
# Second, bench them
python ./TB/bench.py
```
## How to bench one or more specified algorithms
## How to add a new algorithm
## How to transplant the algorithm to embeded system
## Todo list
- [ ] A*
- [ ] BFS
- [ ] DFS
- [ ] Dijkstra
- [ ] FA
- [ ] Write a config file
- [ ] Python benchmark
