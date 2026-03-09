import tkinter as tk
from tkinter import filedialog

from components.terminal import Terminal
from components.buttons import create_button
from styles.theme import BG_COLOR
from core.runner import ArchaeologistRunner

import io
import contextlib


class MainWindow:

    def __init__(self, root):

        self.root = root
        self.runner = ArchaeologistRunner()

        root.title("The Archaeologist")
        root.configure(bg=BG_COLOR)
        root.geometry("1200x800")

        root.bind("<F11>", self.toggle_fullscreen)
        root.bind("<Escape>", self.exit_fullscreen)

        frame = tk.Frame(root, bg=BG_COLOR)
        frame.pack(fill=tk.BOTH, expand=True)

        self.terminal = Terminal(frame)
        self.terminal.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        buttons = tk.Frame(frame, bg=BG_COLOR)
        buttons.pack(pady=5)

        self_btn = create_button(buttons, "SELF RUNNER", self.run_self)
        self_btn.pack(side=tk.LEFT, padx=5)

        run_btn = create_button(buttons, "RUN THE ARCHAEOLOGIST", self.run_external)
        run_btn.pack(side=tk.LEFT, padx=5)

    def toggle_fullscreen(self, event=None):

        state = self.root.attributes("-fullscreen")
        self.root.attributes("-fullscreen", not state)

    def exit_fullscreen(self, event=None):

        self.root.attributes("-fullscreen", False)

    def execute_runner(self, path):

        self.terminal.delete("1.0", tk.END)

        buffer = io.StringIO()

        with contextlib.redirect_stdout(buffer):
            self.runner.run(path)

        lines = buffer.getvalue().splitlines()

        self.terminal.write_lines(self.root, lines)

    def run_self(self):

        self.execute_runner(".")

    def run_external(self):

        path = filedialog.askdirectory()

        if path:
            self.execute_runner(path)