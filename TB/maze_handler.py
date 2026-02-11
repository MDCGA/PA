import random
from typing import List


# Cell class
class Cell:
    def __init__(self) -> None:
        self.walls = {"top": True, "bottom": True, "left": True, "right": True}
        self.visited = False


# generate maze with size of height * width
def make_maze(height, width):
    # DFS
    units = [[Cell() for _ in range(width)] for _ in range(height)]
    stack = [(0, 0)]

    while stack:
        current = stack[-1]
        cx, cy = current
        # print(f"current: {cx}, {cy}")
        units[cy][cx].visited = True
        neighbors = []
        # search for neighbors
        if cx > 0 and not units[cy][cx - 1].visited:
            neighbors.append((cx - 1, cy, "left"))
        if cx < width - 1 and not units[cy][cx + 1].visited:
            neighbors.append((cx + 1, cy, "right"))
        if cy > 0 and not units[cy - 1][cx].visited:
            neighbors.append((cx, cy - 1, "top"))
        if cy < height - 1 and not units[cy + 1][cx].visited:
            neighbors.append((cx, cy + 1, "bottom"))

        if neighbors:
            random.shuffle(neighbors)
            # print(neighbors)
            nx, ny, direction = neighbors.pop()
            stack.append((nx, ny))
            units[cy][cx].walls[direction] = False
            match direction:
                case "left":
                    units[ny][nx].walls["right"] = False
                case "right":
                    units[ny][nx].walls["left"] = False
                case "top":
                    units[ny][nx].walls["bottom"] = False
                case "bottom":
                    units[ny][nx].walls["top"] = False
        else:
            stack.pop()
    return units


# Print the maze in terminal
def print_maze_ASCII(maze: List[List[Cell]]) -> None:
    h, w = len(maze), len(maze[0])
    print(" _" * w)
    for r in range(h):
        print("|", end="")
        for c in range(w):
            print("_" if maze[r][c].walls["bottom"] else " ", end="")
            print("|" if maze[r][c].walls["right"] else " ", end="")
        print("*")


# Pack the maze data in binary
def ASCII_maze_to_binary(maze: List[List[Cell]]) -> bytes:
    # The header contains 2 bytes of height and two bytes of width, in little endian
    h, w = len(maze), len(maze[0])
    header = h.to_bytes(2, "little") + w.to_bytes(2, "little")
    # The maze binary data, each byte contains the info of two units in the maze.
    # The format is left wall|right wall|top wall|bottom wall|left wall|right wall|top wall|bottom wall
    # 1 means the wall exists, 0 means doesn't exist.
    maze_bytes_stream = bytearray()
    maze_flat = [item for row in maze for item in row]
    n = len(maze_flat)
    for i in range(0, n, 2):
        high = (
            maze_flat[i].walls["left"] << 3
            | maze_flat[i].walls["right"] << 2
            | maze_flat[i].walls["top"] << 1
            | maze_flat[i].walls["bottom"] << 0
        )
        low = (
            (
                maze_flat[i + 1].walls["left"] << 3
                | maze_flat[i + 1].walls["right"] << 2
                | maze_flat[i + 1].walls["top"] << 1
                | maze_flat[i + 1].walls["bottom"] << 0
            )
            if i + 1 < n
            else 0
        )
        maze_byte = high << 4 | low
        maze_bytes_stream.append(maze_byte)

    return header + maze_bytes_stream
