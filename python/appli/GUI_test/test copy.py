from tkinter import *

root = Tk()

b = Button(root, text="Delete me", command=lambda: b.destroy())
b.pack()

root.mainloop()