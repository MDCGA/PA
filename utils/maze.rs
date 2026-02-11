use std::io::{self, Read};
// The unit cell of the maze
#[derive(Debug, Clone, Copy)]
pub struct UnitInfo {
    pub left_wall: bool,
    pub right_wall: bool,
    pub top_wall: bool,
    pub bottom_wall: bool,
    pub visited: bool,
}

impl Default for UnitInfo {
    fn default() -> Self {
        Self {
            left_wall: false,
            right_wall: false,
            top_wall: false,
            bottom_wall: false,
            visited: false,
        }
    }
}

// The maze
#[derive(Debug)]
pub struct Maze {
    pub start_x: u16,
    pub start_y: u16,
    pub end_x: u16,
    pub end_y: u16,
    pub rows: u16,
    pub cols: u16,
    pub units: Vec<UnitInfo>,
}

impl Maze {
    pub fn unpack_maze() -> io::Result<Self> {
        let mut stdin = io::stdin();
        let mut buf = [0u8; 2];

        // 2 bytes of start point x and y
        stdin.read_exact(&mut buf)?;
        let start_x = u16::from_le_bytes(buf);
        stdin.read_exact(&mut buf)?;
        let start_y = u16::from_le_bytes(buf);

        // 2 bytes of end point x and y
        stdin.read_exact(&mut buf)?;
        let end_x = u16::from_le_bytes(buf);
        stdin.read_exact(&mut buf)?;
        let end_y = u16::from_le_bytes(buf);

        // 2 bytes rows and 2 bytes columns
        stdin.read_exact(&mut buf)?;
        let rows = u16::from_le_bytes(buf);
        stdin.read_exact(&mut buf)?;
        let cols = u16::from_le_bytes(buf);

        // 分配单元格数组
        let len = (rows as usize) * (cols as usize);
        let mut units = vec![UnitInfo::default(); len];

        // 读取墙信息：每字节包含两个单元格（高4位和低4位）
        for i in (0..len).step_by(2) {
            let mut temp = [0u8; 1];
            stdin.read_exact(&mut temp)?;
            let temp = temp[0];

            // first unit, the high 4 bits
            units[i].left_wall = (temp & 0x80) != 0;
            units[i].right_wall = (temp & 0x40) != 0;
            units[i].top_wall = (temp & 0x20) != 0;
            units[i].bottom_wall = (temp & 0x10) != 0;

            // second unit, the low 4 bits
            if i + 1 < len {
                units[i + 1].left_wall = (temp & 0x08) != 0;
                units[i + 1].right_wall = (temp & 0x04) != 0;
                units[i + 1].top_wall = (temp & 0x02) != 0;
                units[i + 1].bottom_wall = (temp & 0x01) != 0;
            }
        }

        Ok(Maze {
            start_x,
            start_y,
            end_x,
            end_y,
            rows,
            cols,
            units,
        })
    }

    // print maze
    pub fn print_maze_ascii(&self) {
        // top boundary
        for _ in 0..self.cols {
            print!(" _");
        }
        println!(" *");

        // every row
        for r in 0..self.rows {
            print!("|");
            for c in 0..self.cols {
                let i = (r as usize) * (self.cols as usize) + (c as usize);
                let unit = &self.units[i];
                let bottom = if unit.bottom_wall { '_' } else { ' ' };
                let right = if unit.right_wall { '|' } else { ' ' };
                print!("{}{}", bottom, right);
            }
            println!("*");
        }
    }
}

impl Drop for Maze {
    fn drop(&mut self) {
        self.units.clear();
    }
}
