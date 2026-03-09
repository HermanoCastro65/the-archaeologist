import contextlib
import io
import tkinter as tk
from tkinter import filedialog

from components.buttons import create_button
from components.terminal import Terminal
from core.runner import ArchaeologistRunner
from styles.theme import BG_COLOR


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

        # terminal
        self.terminal = Terminal(frame)
        self.terminal.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        # buttons
        buttons = tk.Frame(frame, bg=BG_COLOR)
        buttons.pack(pady=5)

        self_btn = create_button(buttons, "SELF RUNNER", self.run_self)
        self_btn.pack(side=tk.LEFT, padx=5)

        run_btn = create_button(buttons, "RUN THE ARCHAEOLOGIST", self.run_external)
        run_btn.pack(side=tk.LEFT, padx=5)

        repo_btn = create_button(buttons, "SCAN GIT REPOSITORY", self.show_repo_input)
        repo_btn.pack(side=tk.LEFT, padx=5)

        # repo input frame (hidden initially)
        self.repo_frame = tk.Frame(frame, bg=BG_COLOR)

        self.repo_label = tk.Label(
            self.repo_frame,
            text="Repository URL:",
            bg=BG_COLOR,
            fg="#00FF41",
            font=("Courier New", 12),
        )

        self.repo_label.pack(side=tk.LEFT, padx=5)

        self.repo_entry = tk.Entry(
            self.repo_frame,
            width=80,
            bg="black",
            fg="#00FF41",
            insertbackground="#00FF41",
            font=("Courier New", 12),
        )

        self.repo_entry.pack(side=tk.LEFT, padx=5)

        self.repo_entry.bind("<Return>", self.run_repo_scan)

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

    def show_repo_input(self):

        self.repo_frame.pack(pady=10)
        self.repo_entry.focus()

    def run_repo_scan(self, event=None):

        repo_url = self.repo_entry.get()

        # esconder campo de entrada
        self.repo_frame.pack_forget()

        self.repo_entry.delete(0, tk.END)

        self.terminal.delete("1.0", tk.END)

        self.terminal.insert(tk.END, f"Scanning repository:\n{repo_url}\n\n")

        # placeholder até implementar a funcionalidade real
        self.terminal.insert(tk.END, "Git repository scanning not implemented yet.\n")
