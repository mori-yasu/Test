import tkinter as tk
from tkinter import ttk as ttk

def button1_clicked(curr):
    # Combobox
    v1 = tk.StringVar()
    cb = ttk.Combobox(frame1, textvariable=v1)
    
    cb['values']=('Foo', 'Bar', 'Baz')
    cb.set("Foo")
    cb.grid(row=curr[0], column=curr[1])
    curr[0] = curr[0] + 1

if __name__ == '__main__':
    root = tk.Tk()
    root.title('scroll test')
    
    # Frame
    frame1 = tk.Frame(root, padx=10, pady = 10, bg = '#fff000000')
    frame1.grid(row = 0, column = 0)
    canvas = tk.Canvas(frame1, bg = '#000fff000')
    canvas.grid(row = 0, column = 0, padx = 10, pady = 10)
    

    #Button
    button1 = ttk.Button(canvas, text='+', command = lambda:button1_clicked(curr))
    button1.grid(row=0, column=0)
    curr = [1, 0]    

    
    root.mainloop()