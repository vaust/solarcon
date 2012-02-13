'''
Created on 13.02.2012

@author: stegmv
'''

import tkinter as tk

class XtDiagram(tk.Frame):
    
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.Win_X       = 640
        self.Win_Y       = 320
        self.Win_Xoffset = 20
        self.Win_Yoffset = 20        
        self.Win_Xspan   = self.Win_X-2*self.Win_Xoffset
        self.Win_Yspan   = self.Win_Y-2*self.Win_Yoffset
        self.XTicks      = 20
        self.YTicks      =  8
        self.TickLen     =  4 
        self.draw()
        
    def transform(self, x, y):
        x1 =  x + self.Win_Xoffset
        y1 = -y + (self.Win_Y-self.Win_Yoffset) 
        return(x1, y1)
        
    def drawAchses(self):
        (x0, y0) = self.transform(-self.Win_Xoffset, 0)
        (x1, y1) = self.transform( self.Win_Xspan  , 0) 
        self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill='darkgreen', width=1 )
        (x0, y0) = self.transform(0, -self.Win_Yoffset)
        (x1, y1) = self.transform(0,  self.Win_Yspan  )
        self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill='darkgreen', width=1 )

    def drawTicks(self):
        dX = self.Win_Xspan / self.XTicks
        dY=  self.Win_Yspan / self.YTicks
        n = 1
        while( n<self.XTicks):
            (x0, y0) = self.transform(n*dX, -self.TickLen)
            (x1, y1) = self.transform(n*dX, +self.TickLen)
            self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill='darkgreen', width=1 )
            self.xtdiagCnvs.create_text( (x0, y0+2*self.TickLen), fill='darkgreen', text=str(n))
            n += 1
        n = 1
        while( n<self.YTicks):
            (x0, y0) = self.transform( -self.TickLen, n*dY)
            (x1, y1) = self.transform(  self.TickLen, n*dY)
            self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill='darkgreen', width=1 )
            self.xtdiagCnvs.create_text( (x0-2*self.TickLen, y0), fill='darkgreen', text=str(n))
            n += 1

   
    def draw(self):           
        self.xtdiagCnvs = tk.Canvas(self, bg='black', width=640, height=320)
        self.drawAchses()
        self.drawTicks()
        self.xtdiagCnvs.pack()

if __name__ == "__main__":
    root=tk.Tk()
    gui = XtDiagram(root)
    gui.pack()
    root.mainloop()
