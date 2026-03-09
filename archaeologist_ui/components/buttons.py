import tkinter as tk

from styles.theme import BG_COLOR, FG_COLOR, FONT_BOLD


def create_button(parent, text, command):

    return tk.Button(
        parent,
        text=text,
        command=command,
        bg=BG_COLOR,
        fg=FG_COLOR,
        activebackground=BG_COLOR,
        activeforeground=FG_COLOR,
        font=FONT_BOLD,
        highlightthickness=1,
        highlightbackground=FG_COLOR,
    )
