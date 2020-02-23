import tkinter as tk
import tkinter.ttk as ttk
from PIL import Image, ImageTk

class ScrollableFrame(tk.Frame):
    def __init__(self, parent, minimal_canvas_size):
        tk.Frame.__init__(self, parent)

        self.minimal_canvas_size = minimal_canvas_size

        # 縦スクロールバー
        vscrollbar = ttk.Scrollbar(self, orient=tk.VERTICAL)
        vscrollbar.pack(fill=tk.Y, side=tk.RIGHT, expand=False)

        # 横スクロールバー
        hscrollbar = ttk.Scrollbar(self, orient=tk.HORIZONTAL)
        hscrollbar.pack(fill=tk.X, side=tk.BOTTOM, expand=False)

        # Canvas
        self.canvas = tk.Canvas(self, bd=0, highlightthickness=0,
            yscrollcommand=vscrollbar.set, xscrollcommand=hscrollbar.set)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        # スクロールバーをCanvasに関連付け
        vscrollbar.config(command=self.canvas.yview)
        hscrollbar.config(command=self.canvas.xview)

        # Canvasの位置の初期化
        self.canvas.xview_moveto(0)
        self.canvas.yview_moveto(0)

        # スクロール範囲の設定
        self.canvas.config(scrollregion=(0, 0, self.minimal_canvas_size[0], self.minimal_canvas_size[1]))

        # Canvas内にフレーム作成
        self.interior = tk.Frame(self.canvas)
        self.canvas.create_window(0, 0, window=self.interior, anchor='nw')

        # Canvasの大きさを変える関数
        def _configure_interior(event):
            size = (max(self.interior.winfo_reqwidth(), self.minimal_canvas_size[0]),
                max(self.interior.winfo_reqheight(), self.minimal_canvas_size[1]))
            self.canvas.config(scrollregion=(0, 0, size[0], size[1]))
            if self.interior.winfo_reqwidth() != self.canvas.winfo_width():
                self.canvas.config(width = self.interior.winfo_reqwidth())
            if self.interior.winfo_reqheight() != self.canvas.winfo_height():
                self.canvas.config(height = self.interior.winfo_reqheight())

        # 内部フレームの大きさが変わったらCanvasの大きさを変える関数を呼び出す
        self.interior.bind('<Configure>', _configure_interior)
    

if __name__ == "__main__":

    class SampleApp(tk.Tk):
        def __init__(self, *args, **kwargs):
            root = tk.Tk.__init__(self, *args, **kwargs)
            
            self.frame = ScrollableFrame(root, [100, 100])
            self.frame.pack()
            self.label = ttk.Label(text="ウィンドウを縮めてみてください。スクロールバーが出てきます.")
            self.label.pack()
            buttons = []
            #Button
            self.button1 = ttk.Button(self.frame.interior, text='+', command = lambda:self.button1_clicked(self.curr))
            self.button1.grid(row=0, column=0)
            self.curr = [1, 0] 
            # for i in range(20):
            #     buttons.append(Button(, text="Button " + str(i)))
            #     buttons[-1].pack()

        #ボタンクリックイベント
        def button1_clicked(self, curr):
            # Combobox
            v1 = tk.StringVar()
            self.cb = ttk.Combobox(self.frame.interior, textvariable=v1)
            
            self.cb['values']=('Foo', 'Bar', 'Baz')
            self.cb.set("Foo")
            self.cb.grid(row=curr[0], column=curr[1])
            curr[0] = curr[0] + 1

    app = SampleApp()
    app.mainloop()