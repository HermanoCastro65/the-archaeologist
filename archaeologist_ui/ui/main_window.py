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

        self.terminal = Terminal(frame)
        self.terminal.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        buttons = tk.Frame(frame, bg=BG_COLOR)
        buttons.pack(pady=5)

        self.self_btn = create_button(buttons, "SELF RUNNER", self.run_self)
        self.self_btn.pack(side=tk.LEFT, padx=5)

        self.run_btn = create_button(buttons, "RUN THE ARCHAEOLOGIST", self.run_external)
        self.run_btn.pack(side=tk.LEFT, padx=5)

        self.repo_btn = create_button(buttons, "SCAN GIT REPOSITORY", self.show_repo_input)
        self.repo_btn.pack(side=tk.LEFT, padx=5)

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

        self.search_frame = tk.Frame(frame, bg=BG_COLOR)

        self.search_label = tk.Label(
            self.search_frame,
            text="Search file:",
            bg=BG_COLOR,
            fg="#00FF41",
            font=("Courier New", 12),
        )

        self.search_label.pack(side=tk.LEFT, padx=5)

        self.search_entry = tk.Entry(
            self.search_frame,
            width=40,
            bg="black",
            fg="#00FF41",
            insertbackground="#00FF41",
            font=("Courier New", 12),
        )

        self.search_entry.pack(side=tk.LEFT, padx=5)
        self.search_entry.bind("<Return>", self.search_file)

    def toggle_fullscreen(self, event=None):

        state = self.root.attributes("-fullscreen")
        self.root.attributes("-fullscreen", not state)

    def exit_fullscreen(self, event=None):

        self.root.attributes("-fullscreen", False)

    def execute_runner(self, path):

        self.disable_ui()

        self.terminal.delete("1.0", tk.END)

        buffer = io.StringIO()

        with contextlib.redirect_stdout(buffer):
            self.runner.run(path)

        lines = buffer.getvalue().splitlines()

        def on_finish():

            self.enable_ui()
            self.search_frame.pack(pady=10)
            self.search_entry.focus()

        self.terminal.write_lines(self.root, lines, on_finish)

    def run_self(self):

        self.execute_runner(".")

    def run_external(self):

        path = filedialog.askdirectory()

        if path:
            self.execute_runner(path)

    def show_repo_input(self):

        if self.self_btn["state"] == "disabled":
            return

        self.repo_frame.pack(pady=10)
        self.repo_entry.focus()

    def run_repo_scan(self, event=None):

        repo_url = self.repo_entry.get().strip()

        if not repo_url:
            return

        self.repo_frame.pack_forget()
        self.repo_entry.delete(0, tk.END)

        self.execute_runner(repo_url)

    def search_file(self, event=None):

        if self.self_btn["state"] == "disabled":
            return

        filename = self.search_entry.get().strip()

        if not filename:
            return

        self.disable_ui()

        buffer = io.StringIO()

        with contextlib.redirect_stdout(buffer):
            self.runner.search_file(filename)

        lines = buffer.getvalue().splitlines()

        def on_finish():
            self.enable_ui()

        self.terminal.write_lines(self.root, lines, on_finish)

    def disable_ui(self):

        self.self_btn.config(state="disabled")
        self.run_btn.config(state="disabled")
        self.repo_btn.config(state="disabled")
        self.search_entry.config(state="disabled")

    def enable_ui(self):

        self.self_btn.config(state="normal")
        self.run_btn.config(state="normal")
        self.repo_btn.config(state="normal")
        self.search_entry.config(state="normal")
