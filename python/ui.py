import sys
import os
import tkinter as tk
from tkinter.scrolledtext import ScrolledText

current_dir = os.path.dirname(__file__)
project_root = os.path.abspath(os.path.join(current_dir, ".."))
build_python = os.path.join(project_root, "build", "python")

sys.path.insert(0, build_python)

import archaeologist_py


class ArchaeologistUI:

    def __init__(self, root):

        self.root = root
        self.root.title("The Archaeologist")

        self.root.configure(bg="black")

        self.root.geometry("1200x800")
        self.root.resizable(True, True)

        self.root.bind("<F11>", self.toggle_fullscreen)
        self.root.bind("<Escape>", self.exit_fullscreen)

        frame = tk.Frame(root, bg="black")
        frame.pack(fill=tk.BOTH, expand=True)

        self.text = ScrolledText(
            frame,
            bg="black",
            fg="#00FF41",
            insertbackground="#00FF41",
            font=("Courier New", 12),
            borderwidth=0
        )

        self.text.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        run_btn = tk.Button(
            frame,
            text="RUN SCANNER",
            command=self.run_scanner,
            bg="black",
            fg="#00FF41",
            activebackground="black",
            activeforeground="#00FF41",
            font=("Courier New", 12, "bold"),
            highlightthickness=1,
            highlightbackground="#00FF41"
        )

        run_btn.pack(pady=5)

    def toggle_fullscreen(self, event=None):
        state = self.root.attributes("-fullscreen")
        self.root.attributes("-fullscreen", not state)

    def exit_fullscreen(self, event=None):
        self.root.attributes("-fullscreen", False)

    def type_output(self, lines, index=0):

        if index >= len(lines):
            return

        self.text.insert(tk.END, lines[index] + "\n")
        self.text.see(tk.END)

        self.root.after(20, self.type_output, lines, index + 1)

    def run_scanner(self):

        self.text.delete("1.0", tk.END)

        runner = archaeologist_py.SelfRunner()

        import io
        import contextlib

        buffer = io.StringIO()

        with contextlib.redirect_stdout(buffer):
            runner.run()

        output = buffer.getvalue()
        lines = output.splitlines()

        self.type_output(lines)


root = tk.Tk()

app = ArchaeologistUI(root)

root.mainloop()