import sys
import os
import tkinter as tk
from tkinter.scrolledtext import ScrolledText

# localizar módulo compilado
current_dir = os.path.dirname(__file__)
project_root = os.path.abspath(os.path.join(current_dir, ".."))
build_python = os.path.join(project_root, "build", "python")

sys.path.insert(0, build_python)

import archaeologist_py


class ArchaeologistUI:

    def __init__(self, root):

        self.root = root
        self.root.title("The Archaeologist")

        # MATRIX STYLE
        self.root.configure(bg="black")

        self.text = ScrolledText(
            root,
            width=110,
            height=40,
            bg="black",
            fg="#00FF41",
            insertbackground="#00FF41",
            font=("Courier New", 11),
            borderwidth=0
        )

        self.text.pack(padx=10, pady=10)

        run_btn = tk.Button(
            root,
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

    def run_scanner(self):

        self.text.delete("1.0", tk.END)

        runner = archaeologist_py.SelfRunner()

        import io
        import contextlib

        buffer = io.StringIO()

        with contextlib.redirect_stdout(buffer):
            runner.run()

        output = buffer.getvalue()

        self.text.insert(tk.END, output)


root = tk.Tk()

app = ArchaeologistUI(root)

root.mainloop()