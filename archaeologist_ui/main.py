import sys
import os

sys.path.append(os.path.dirname(__file__))

import tkinter as tk
from ui.main_window import MainWindow


def main():

    root = tk.Tk()

    MainWindow(root)

    root.mainloop()


if __name__ == "__main__":
    main()