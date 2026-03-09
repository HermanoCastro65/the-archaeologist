import tkinter as tk
from tkinter.scrolledtext import ScrolledText

from styles.theme import BG_COLOR, FG_COLOR, FONT


class Terminal(ScrolledText):
    def __init__(self, parent):

        super().__init__(
            parent, bg=BG_COLOR, fg=FG_COLOR, insertbackground=FG_COLOR, font=FONT, borderwidth=0
        )

    def write_lines(self, root, lines, index=0):

        if index >= len(lines):
            return

        self.insert(tk.END, lines[index] + "\n")
        self.see(tk.END)

        root.after(1, self.write_lines, root, lines, index + 1)
