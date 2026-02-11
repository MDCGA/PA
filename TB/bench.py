import subprocess
from pathlib import Path

from maze_handler import ASCII_maze_to_binary, make_maze, print_maze_ASCII

BENCH_DIR = Path(__file__).resolve().parent
BUILD = BENCH_DIR.parent / "build"
BUILD.mkdir(exist_ok=True)


maze = make_maze(3, 3)
print_maze_ASCII(maze)
START_X, START_Y = 0, 0
END_X, END_Y = 2, 2
input_stream = (
    START_X.to_bytes(2, "little")
    + START_Y.to_bytes(2, "little")
    + END_X.to_bytes(2, "little")
    + END_Y.to_bytes(2, "little")
    + ASCII_maze_to_binary(maze)
)
print(f"STDIN: {input_stream.hex(':')}")
Path(BUILD / "maze.bin").write_bytes(input_stream)

r = subprocess.run([BUILD / "dfs_c"], input=input_stream, capture_output=True)
print(r.stdout.decode())
print(r.stderr.decode())
if r.returncode != 0:
    print(r.returncode)
