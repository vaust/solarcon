'''
Created on 07.03.2012

@author: stegmv
'''

import tkinter as tk

class Thermometer(tk.Frame):
    
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.width  = 100
        self.height = 400
        self.physSpan    =  70    # °C
        self.physOffs    = -50    # °C
        self.physTickLen =  10    # °C
        self.relScaleX   =   0.50
        self.relHgX      =   0.02
        self.relHgWidth  =   0.40
        
        self.draw()
        
    def draw(self):
        self.cnvs = tk.Canvas(self, width=self.width, height=self.height, bg='white')
        self.drawScale()
        self.cnvs.pack()

    def drawScale(self):
        # Achse zeichnen
        x0, y0 = self.relScaleX * self.width, self.height
        x1, y1 = self.relScaleX * self.width, 0
        self.yAchsenId = self.cnvs.create_line(x0, y0, x1, y1, fill='black', width=1, arrow=tk.LAST)
        
        # Ticks zeichnen
        nTicks = self.physSpan / self.physTickLen
        dy = self.height / nTicks
        self.yTickId = []
        self.yTextId = []
        y = 0
        n = 0
        while (n<nTicks):
            x0, y0 = self.relScaleX * self.width - 10, self.height-y
            x1, y1 = self.relScaleX * self.width     , self.height-y
            ytickId = self.cnvs.create_line(x0, y0, x1, y1, width=1)
            ytextId = self.cnvs.create_text(x0-10, y0, text=str(n*self.physTickLen+self.physOffs))
            self.yTickId.append(ytickId)
            self.yTextId.append(ytextId)
            y += dy
            n += 1
        if (self.height/self.physSpan > 2.0):
            dy = self.height/self.physSpan
            y  = 0
            n  = 0
            while (n<self.physSpan-3):
                if(n % 5 == 0):
                    x0, y0 = self.relScaleX * self.width - 8, self.height-y
                else:
                    x0, y0 = self.relScaleX * self.width - 5, self.height-y
                x1, y1 = self.relScaleX * self.width    , self.height-y
                ytickId = self.cnvs.create_line(x0, y0, x1, y1, width=1)
                y += dy
                n += 1
        # self.HgId=self.cnvs.create_rectangle(0,0,0,0)
        self.HgId = self.cnvs.create_line(0,0,0,0)
                                             
    def plotHg(self, temp):
        y = (temp-self.physOffs)/self.physSpan*self.height
        x0, y0 = (self.relScaleX + self.relHgX) * self.width, self.height
        x1, y1 = x0 + self.relHgWidth * self.width, self.height-y
        self.cnvs.delete(self.HgId)
        # self.HgId = self.cnvs.create_rectangle(x0, y0, x1, y1, fill='red')
        self.HgId = self.cnvs.create_line(x1, y1, x0, y1, fill='red', width=15, arrow=tk.LAST)
         
if __name__ == "__main__" :
    import random
    
    def doit():
        th.plotHg(random.gauss(0.0, 5.0))
        root.after(2000, doit)
    
    root=tk.Tk()
    th = Thermometer(root)
    th.plotHg(25.0)
    th.pack()
    root.after(2000, doit)
    root.mainloop()


    
    