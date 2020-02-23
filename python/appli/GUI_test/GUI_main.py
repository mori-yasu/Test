import tkinter as tk
import tkinter.ttk as ttk

#メインウィンドウ
main_win = tk.Tk()
main_win.title('GUI test')
main_win.geometry('800x400')

VehilceGrp = ttk.Labelframe(main_win, text = 'Vehicle(Add Just What you See)', borderwidth = 15, relief="groove")
VehilceGrp.grid(row = 0, column = 0, sticky = tk.W)

#車両
class plus_Row_Vehicle():
    def __init__(self, VehilceGrp, curr_vehicle_matrix, Totaldict):
        self.TypeCB = ttk.Combobox(VehilceGrp, value = ['トランク付き', 'トランクなし','トラック','バイク'])
        self.TypeCB.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.N)
        self.TypeCB.bind('<<ComboboxSelected>>', lambda event: self.save_selecedCB(event, Totaldict))
        curr_vehicle_matrix[1] = curr_vehicle_matrix[1] + 1
        self.ActionLB = tk.Listbox(VehilceGrp, listvariable=tk.StringVar(value=['直進', '右折','左折','停車']), height = 3, width = 5)
        self.ActionLB.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1])
        curr_vehicle_matrix[1] = curr_vehicle_matrix[1] + 1
        self.CategolyLB = ttk.Combobox(VehilceGrp, value=['先行車', '隣接車','停止車両','隣接車→先行車','先行車→隣接者'])
        self.CategolyLB.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.N)
        curr_vehicle_matrix[1] = curr_vehicle_matrix[1] + 1
        self.ColorLB = ttk.Combobox(VehilceGrp, value=['黒', '白','赤','青','その他'])
        self.ColorLB.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.N)
        curr_vehicle_matrix[0] = curr_vehicle_matrix[0] + 1
        curr_vehicle_matrix[1] = 0
        #空のdictを作成する
    
    #そのdictに対し、代入操作を行う。
    def save_selecedCB(self, event, Totaldict):
        print(self.TypeCB.get())
        Totaldict['Type'] = []
        Totaldict['Type'] = [self.TypeCB.get()]        

        


IntegtatedDict = {}

LineLabel = ttk.Label(VehilceGrp, text = 'Add')
LineLabel.grid(row = 0, column = 0, sticky = tk.E)
LineButton = ttk.Button(VehilceGrp, text = '+',width = 2, command = lambda: plus_Row_Vehicle(VehilceGrp, curr_vehicle_matrix, IntegtatedDict))
LineButton.grid(row = 0, column = 1,sticky = tk.W)

curr_vehicle_matrix = [1, 0]

Type = ttk.Label(VehilceGrp,text = 'type', state = 'readonly',borderwidth=1, relief="groove")
Type.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.NSEW)
curr_vehicle_matrix[1] = curr_vehicle_matrix[1] + 1
Action = ttk.Label(VehilceGrp,text = 'Action', state = 'readonly',borderwidth=1, relief="groove")
Action.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.NSEW)
curr_vehicle_matrix[1] = curr_vehicle_matrix[1] + 1
Categoly = ttk.Label(VehilceGrp,text = 'Categoly', state = 'readonly',borderwidth=1, relief="groove")
Categoly.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.NSEW)
curr_vehicle_matrix[1] = curr_vehicle_matrix[1] + 1
Color = ttk.Label(VehilceGrp,text = 'Color', state = 'readonly',borderwidth=1, relief="groove")
Color.grid(row = curr_vehicle_matrix[0], column = curr_vehicle_matrix[1], sticky = tk.NSEW)
curr_vehicle_matrix[0] = curr_vehicle_matrix[0] + 1
curr_vehicle_matrix[1] = 0 

plus_Row_Vehicle(VehilceGrp, curr_vehicle_matrix, IntegtatedDict)
curr_vehicle_matrix[0] = curr_vehicle_matrix[0] + 1
curr_vehicle_matrix[1] = 0 

#歩行者
class plus_PedRow():
    def __init__(self, PedGrp, curr_pedmatrix):
        SexCB = ttk.Combobox(PedGrp, value=['男性', '女性','ダミー','その他'])
        SexCB.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.N)
        curr_pedmatrix[1] = curr_pedmatrix[1] + 1
        AgeCB = ttk.Combobox(PedGrp, value=['子供', '青年','大人','老人'])
        AgeCB.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.N)
        curr_pedmatrix[1] = curr_pedmatrix[1] + 1
        ShapeLB = ttk.Combobox(PedGrp, value=['やせ型', '普通','肥満体'])
        ShapeLB.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.N)
        curr_pedmatrix[1] = curr_pedmatrix[1] + 1
        ActionLB = tk.Listbox(PedGrp, listvariable = tk.StringVar(value = ['左','右','奥','手前','停止']), height = 3)
        ActionLB.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.N)
        curr_pedmatrix[0] = curr_pedmatrix[0] + 1
        curr_pedmatrix[1] = 0 

PedGrp = ttk.Labelframe(main_win, text = 'Pedestrian(Add Just What you See)', borderwidth = 15)
PedGrp.grid(row = 2, column = 0, sticky = tk.W)
curr_pedmatrix = [0,0]
Label = ttk.Label(PedGrp,text = 'Add')
Label.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.E)
PedButton = ttk.Button(PedGrp, text = '+',width = 2, command = lambda: plus_PedRow(PedGrp, curr_pedmatrix))
curr_pedmatrix[1] = curr_pedmatrix[1] + 1
PedButton.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.W)
curr_pedmatrix[0] = curr_pedmatrix[0] + 1
curr_pedmatrix[1] = 0

Sex = ttk.Label(PedGrp,text = 'Sex', state = 'readonly',borderwidth=1, relief="groove")
Sex.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.NSEW)
curr_pedmatrix[1] = curr_pedmatrix[1] + 1
Age = ttk.Label(PedGrp,text = 'Age', state = 'readonly',borderwidth=1, relief="groove")
Age.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.EW)
curr_pedmatrix[1] = curr_pedmatrix[1] + 1
Shape = ttk.Label(PedGrp,text = 'Shape', state = 'readonly',borderwidth=1, relief="groove")
Shape.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.NSEW)
curr_pedmatrix[1] = curr_pedmatrix[1] + 1
Action = ttk.Label(PedGrp,text = 'Action', state = 'readonly',borderwidth=1, relief="groove")
Action.grid(row = curr_pedmatrix[0], column = curr_pedmatrix[1], sticky = tk.NSEW)
curr_pedmatrix[0] = curr_pedmatrix[0] + 1
curr_pedmatrix[1] = 0 

plus_PedRow(PedGrp, curr_pedmatrix)
curr_pedmatrix[0] = curr_pedmatrix[0] + 1
curr_pedmatrix[1] = 0 


main_win.mainloop()