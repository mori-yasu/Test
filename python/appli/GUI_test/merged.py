from tkinter import *
from tkinter import ttk as ttk
class VerticalScrolledFrame(Frame):
    """A pure Tkinter scrollable frame that actually works!
    * Use the 'interior' attribute to place widgets inside the scrollable frame
    * Construct and pack/place/grid normally
    * This frame only allows vertical scrolling

    """
    def __init__(self, parent, *args, **kw):
        Frame.__init__(self, parent, *args, **kw)            

        # スクロールバーの作成
        vscrollbar = Scrollbar(self, orient=VERTICAL)
        vscrollbar.pack(fill=Y, side=RIGHT, expand=FALSE)
        canvas = Canvas(self, bd=0, highlightthickness=0,
                        yscrollcommand=vscrollbar.set)
        canvas.pack(side=LEFT, fill=BOTH, expand=TRUE)
        vscrollbar.config(command=canvas.yview)

        # ビューをリセット
        canvas.xview_moveto(0)
        canvas.yview_moveto(0)

        # create a frame inside the canvas which will be scrolled with it
        self.interior = interior = Frame(canvas)
        interior_id = canvas.create_window(0, 0, window=interior,
                                           anchor=NW)

        # track changes to the canvas and frame width and sync them,
        # also updating the scrollbar
        def _configure_interior(event):
            # update the scrollbars to match the size of the inner frame
            size = (interior.winfo_reqwidth(), interior.winfo_reqheight())
            canvas.config(scrollregion="0 0 %s %s" % size)
            if interior.winfo_reqwidth() != canvas.winfo_width():
                # update the canvas's width to fit the inner frame
                canvas.config(width=interior.winfo_reqwidth())
        #Configureバインド…ウィンドウサイズが変更されたときに発生するイベント
        interior.bind('<Configure>', _configure_interior)

        def _configure_canvas(event):
            if interior.winfo_reqwidth() != canvas.winfo_width():
                # update the inner frame's width to fill the canvas
                canvas.itemconfigure(interior_id, width=canvas.winfo_width())
        canvas.bind('<Configure>', _configure_canvas)


if __name__ == "__main__":

    class SampleApp(Tk):
        def __init__(self, *args, **kwargs):
            root = Tk.__init__(self, *args, **kwargs)
#            root.resize('800x600')

            self.frame = VerticalScrolledFrame(root)
            self.frame.pack()
            self.label = Label(text="ウィンドウを縮めてみてください。スクロールバーが出てきます.")
            self.label.pack()
            buttons = []
            #Button
            self.button1 = ttk.Button(self.frame.interior, text='+', command = lambda:self.plus_button1_clicked(self.curr))
            self.button1.grid(row=0, column=0)
            self.button2 = ttk.Button(self.frame.interior, text='-', command = lambda:self.minus_button1_clicked(self.curr))
            self.button2.grid(row=0, column=1)

            self.curr = [1, 0] 
            # for i in range(20):
            #     buttons.append(Button(, text="Button " + str(i)))
            #     buttons[-1].pack()
        def minus_button1_clicked(self, curr):
            self.cb.destroy()
            curr[0] = curr[0] - 1

        #ボタンクリックイベント
        def plus_button1_clicked(self, curr):
            # Combobox
            v1 = StringVar()
            self.cb = ttk.Combobox(self.frame.interior, textvariable=v1)
            
            self.cb['values']=('Foo', 'Bar', 'Baz')
            self.cb.set("Foo")
            self.cb.grid(row=curr[0], column=curr[1])
            curr[0] = curr[0] + 1

    app = SampleApp()
    app.mainloop()