# Based on https://stackoverflow.com/a/30045893
from tkinter import Canvas, Button, Tk


MAP_NB_ROW = 31
MAP_NB_COL = 31
MAP_CELL_SIZE = 30

OUTPUT_FILENAME = "map_output"

BORDER_COLOR = "black"
EMPTY_COLOR = "white"
FILLED_COLOR = "black"
GRID_OFFSET = 50


class Cell():
    def __init__(self, master, x, y):
        self.master = master
        self.x = x
        self.y = y
        self.fill = False

    def switch(self):
        self.fill = not self.fill

    def draw(self):
        if self.master is not None:
            outline = BORDER_COLOR

            if self.fill:
                fill = FILLED_COLOR
            else:
                fill = EMPTY_COLOR

            xmin = self.x * MAP_CELL_SIZE + GRID_OFFSET
            xmax = xmin + MAP_CELL_SIZE
            ymin = self.y * MAP_CELL_SIZE + GRID_OFFSET
            ymax = ymin + MAP_CELL_SIZE

            self.master.create_rectangle(
                xmin, ymin, xmax, ymax, fill=fill, outline=outline)


class Grid(Canvas):
    def __init__(self, master):
        Canvas.__init__(self, master,
                        width=MAP_CELL_SIZE * MAP_NB_COL + 2 * GRID_OFFSET,
                        height=MAP_CELL_SIZE * MAP_NB_ROW + 2 * GRID_OFFSET)

        self.save_button = Button(master, text="Save", command=self.save_grid)
        self.save_button.pack()

        self.grid = []
        for row in range(MAP_NB_ROW):
            line = []
            for col in range(MAP_NB_COL):
                line.append(Cell(self, col, row))
            self.grid.append(line)

        self.switched = []

        self.bind("<Button-1>", self.handle_mouse_click)
        self.bind("<B1-Motion>", self.handle_mouse_motion)
        self.bind("<ButtonRelease-1>", lambda event: self.switched.clear())

        self.draw()

    def draw(self):
        for row in self.grid:
            for cell in row:
                cell.draw()

        for row in range(MAP_NB_ROW):
            y_pos = MAP_CELL_SIZE * (row + 1) - (MAP_CELL_SIZE // 2)
            self.create_text(30, y_pos + GRID_OFFSET, text=str(row + 1))
        for col in range(MAP_NB_COL):
            x_pos = MAP_CELL_SIZE * (col + 1) - (MAP_CELL_SIZE // 2)
            self.create_text(x_pos + GRID_OFFSET, 30, text=str(col + 1))

    def get_coords(self, event):
        row = int((event.y - GRID_OFFSET) / MAP_CELL_SIZE)
        col = int((event.x - GRID_OFFSET) / MAP_CELL_SIZE)
        return row, col

    @staticmethod
    def inside_grid(event):
        return GRID_OFFSET <= event.x < GRID_OFFSET + MAP_NB_ROW * MAP_CELL_SIZE and \
               GRID_OFFSET <= event.y < GRID_OFFSET + MAP_NB_COL * MAP_CELL_SIZE

    def handle_mouse_click(self, event):
        if not self.inside_grid(event):
            return
        row, col = self.get_coords(event)
        cell = self.grid[row][col]
        cell.switch()
        cell.draw()
        self.switched.append(cell)

    def handle_mouse_motion(self, event):
        if not self.inside_grid(event):
            return
        row, col = self.get_coords(event)
        cell = self.grid[row][col]

        if cell not in self.switched:
            cell.switch()
            cell.draw()
            self.switched.append(cell)

    def save_grid(self):
        output = ""
        for row in self.grid:
            for cell in row:
                if cell.fill:
                    output += 'X'
                else:
                    output += '.'
            output += '\n'
        with open(OUTPUT_FILENAME, 'w+') as f:
            f.write(output)


if __name__ == "__main__":
    app = Tk()

    grid = Grid(app)
    grid.pack()

    app.mainloop()
