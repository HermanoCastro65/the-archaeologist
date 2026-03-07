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

        self.text = ScrolledText(root, width=100, height=40)
        self.text.pack(padx=10, pady=10)

        run_btn = tk.Button(root, text="Run Scanner", command=self.run_scanner)
        run_btn.pack()

    def run_scanner(self):

        self.text.delete("1.0", tk.END)

        runner = archaeologist_py.SelfRunner()

        # capturar output
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