use std::io;
use utils::Maze;
fn main() -> io::Result<()> {
    let maze = Maze::unpack_maze()?;
    maze.print_maze_ascii();
    Ok(())
}
