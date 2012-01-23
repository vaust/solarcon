'''
Created on 23.01.2012

@author: stegmv
'''

import tkinter as tk
import tkinter.ttk as ttk

class GuiOverview(tk.Frame):
    '''
    classdocs
    '''


    def __init__(self, master=None):
        '''
        Constructor
        '''
        tk.Frame.__init__(self, master)
        # self.pack()
        self.draw()
        
    def cllbck(self, event): 
        print('Mouse clicked at ', self.main.canvasx(event.x), self.main.canvasy(event.y) )
    
    def draw(self):
        self.vbar = ttk.Scrollbar( self, orient=tk.VERTICAL)
        self.hbar = ttk.Scrollbar( self, orient=tk.HORIZONTAL)

        self.main = tk.Canvas(self, bg='white', scrollregion=(0,0,2000,2000),
                       yscrollcommand=self.vbar.set, xscrollcommand=self.hbar.set, width=1220, height=560)
        self.main.bind('<Button-1>', self.cllbck)
        self.bgpic = tk.PhotoImage(file='Visualisierung.gif')
        
        self.main.create_image(1000,1000, image=self.bgpic)
                             
        self.vbar.grid(row=0, column=1, sticky=tk.NS)
        self.hbar.grid(row=1, column=0, sticky=tk.EW)
        self.main.grid(row=0, column=0, sticky=tk.NSEW)

        self.vbar.config(command=self.main.yview)
        self.hbar.config(command=self.main.xview)

   
        
root=tk.Tk()
gui = GuiOverview(root)
gui.pack()
gui.mainloop()





        