#特別なクラス定義はここに書くように
import tkinter as tk
import tkinter.ttk as ttk
from enum import Enum
from enum import auto
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#ピクセル座標
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
class pix(Enum):
    Is = 0
    Js = auto()
    Ie = auto()
    Je = auto()

#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
#ウィンドウのスクロールバーの作成
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
class VerticalScrolledFrame(tk.Frame):
    """A pure Tkinter scrollable frame that actually works!
    * Use the 'interior' attribute to place widgets inside the scrollable frame
    * Construct and pack/place/grid normally
    * This frame only allows vertical scrolling

    """
    def __init__(self, parent, win_size, win_grid, *args, **kw):
        tk.Frame.__init__(self, parent, *args, **kw)
        # スクロールバーの作成
        vscrollbar = tk.Scrollbar(self, orient = tk.VERTICAL)
        vscrollbar.grid(row = win_grid[0], column = win_grid[1] + 1, sticky = tk.NS + tk.W)
        # キャンバスと連結
        canvas = tk.Canvas(self, bd = 0, highlightthickness = 0,
                        yscrollcommand = vscrollbar.set, width = win_size[0], height = win_size[1])
        canvas.grid(row = win_grid[0], column = win_grid[1], sticky = tk.NSEW)
        vscrollbar.config(command=canvas.yview)

        # ビューをリセット
        canvas.xview_moveto(0)
        canvas.yview_moveto(0)

        # キャンバス内にフレーム用意
        self.interior = interior = tk.Frame(canvas, width = win_size[0], height = win_size[1])
        interior_id = canvas.create_window(0, 0, window = interior,
                                           anchor = tk.NW)

        # キャンバス-フレームのサイズ変更をトラック、これらを同期する。
        #スクロールバーも更新
        def _configure_interior(event):
            # フレームに変化にあわせてスクロール領域更新
            size = (interior.winfo_reqwidth(), interior.winfo_reqheight())
            canvas.config(scrollregion="0 0 %s %s" % size)
            if interior.winfo_reqwidth() != canvas.winfo_width():
                # フレーム幅にキャンバスサイズをフィッティング
                canvas.config(width=interior.winfo_reqwidth())
        #Configureバインド→ウィジェットのサイズ変更、スクロールバー移動等あったときにコール
        interior.bind('<Configure>', _configure_interior)

        def _configure_canvas(event):
            if interior.winfo_reqwidth() != canvas.winfo_width():
                # キャンバスサイズにあわせてフレーム幅を更新
                canvas.itemconfigure(interior_id, width=canvas.winfo_width())
        canvas.bind('<Configure>', _configure_canvas)
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
