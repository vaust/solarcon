'''
Created on 09.02.2012

@author: stegmv
'''
import tkinter as tk
# import tkinter.ttk as ttk
import signals

HFARBE  = 'LightGoldenrod1'

class GuiParam(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.paramLbl = dict()
        self.paramValEntry = dict()
        self.draw()
    
    def draw(self):
        i = j = 0 # i: Zeile j: Spalte
        for name in signals.PARAMETERS:
            self.paramLbl[name] = tk.Label(self, text=name+" = ")
            self.paramLbl[name].grid(row=i, column=j, padx=5, pady=5, sticky=tk.NW)
            self.paramValEntry[name] = tk.Entry(self, relief='sunken', width=12, bg=HFARBE)
            self.paramValEntry[name].grid(row=i, column=j+1, padx=5, pady=5, sticky=tk.NW)
            if (i<10):
                i += 1
            else:
                i  = 0
                j += 2
        
        self.paramLesenRamBttn = tk.Button(self, text='Aus RAM Lesen')
        self.paramLesenRamBttn.grid(row=11, column=0, columnspan=2, padx=5, pady=5, sticky=tk.NE)
        self.paramSchreibenRamBttn = tk.Button(self, text='In RAM Schreiben')
        self.paramSchreibenRamBttn.grid(row=11, column=2, columnspan=2, padx=5, pady=5, sticky=tk.NE)
        self.paramDateiLesenBttn = tk.Button(self, text='Parameterdatei lesen')
        self.paramDateiLesenBttn.grid(row=11, column=4, columnspan=2, padx=5, pady=5, sticky=tk.NE)
        self.paramDateiSchreibenBttn = tk.Button(self, text='Parameterdatei schreiben')
        self.paramDateiSchreibenBttn.grid(row=11, column=6, columnspan=2, padx=5, pady=5, sticky=tk.NE)
                
if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiParam(root)
    gui.pack()
    root.mainloop()
