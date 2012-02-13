'''
Created on 13.02.2012

@author: stegmv
'''

import tkinter as tk

class XtDiagram(tk.Frame):
    Win_X       = 1024
    Win_Y       = 320
    Win_Xoffset = 25
    Win_Yoffset = 20        

    XTicks       = 20
    YTicks       =  8
    TickLen     =  4 
    
    PhysX_TickUnit  = 10   # sec
    PhysY_TickUnit  =  1   # °C
    PhysX_Offs      =  0   # sec
    PhysY_Offs      = 36   # °C

    BackColor   = 'black'
    Achsenfarbe = 'darkgreen'
    XAchsentext = 'sec'
    YAchsentext = '°C'

    def __init__(self, master=None):
        tk.Frame.__init__(self, master, relief=tk.SUNKEN)

        self.Win_Xspan   = self.Win_X-2*self.Win_Xoffset
        self.Win_Yspan   = self.Win_Y-2*self.Win_Yoffset

        self.LastPhysX   = self.PhysX_Offs
        self.LastPhysY   = self.PhysY_Offs
        
        self.draw()

    def cllbck(self, event): 
        print('Mouse clicked at ', self.xtdiagCnvs.canvasx(event.x), self.xtdiagCnvs.canvasy(event.y) )
        
    def transform(self, x, y):
        x1 =  x + self.Win_Xoffset
        y1 = -y + (self.Win_Y-self.Win_Yoffset) 
        return (x1, y1)
    
    def transformPhystoLogic(self, physX, physY):    
        x1=(physX-self.PhysX_Offs)/self.PhysX_TickUnit * self.Win_Xspan/self.XTicks
        y1=(physY-self.PhysY_Offs)/self.PhysY_TickUnit * self.Win_Yspan/self.YTicks
        (x2, y2) = self.transform(x1, y1)
        return (x2, y2)
    
    def drawAchses(self):
        (x0, y0) = self.transform(-self.Win_Xoffset, 0)
        (x1, y1) = self.transform( self.Win_Xspan  , 0) 
        self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1, arrow=tk.LAST )
        (x0, y0) = self.transform(0, -self.Win_Yoffset)
        (x1, y1) = self.transform(0,  self.Win_Yspan  )
        self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1, arrow=tk.LAST )
    
    def drawTicks(self):
        dX = self.Win_Xspan / self.XTicks
        dY=  self.Win_Yspan / self.YTicks
        n = 1
        while( n<self.XTicks):
            (x0, y0) = self.transform(n*dX, -self.TickLen)
            (x1, y1) = self.transform(n*dX, +self.TickLen)
            self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1 )
            self.xtdiagCnvs.create_text( (x0, y0+2*self.TickLen), fill=self.Achsenfarbe, 
                                         text=str(n*self.PhysX_TickUnit+self.PhysX_Offs))
            n += 1

        (x0, y0) = self.transform(n*dX, -3*self.TickLen)
        self.xtdiagCnvs.create_text( (x0, y0), fill=self.Achsenfarbe, text=self.XAchsentext )
        
        n = 1
        while( n<self.YTicks):
            (x0, y0) = self.transform( -self.TickLen, n*dY)
            (x1, y1) = self.transform(  self.TickLen, n*dY)
            self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1 )
            self.xtdiagCnvs.create_text( (x0-2*self.TickLen, y0), fill=self.Achsenfarbe, 
                                         text=str(n*self.PhysY_TickUnit+self.PhysY_Offs))
            n += 1
   
        (x0, y0) = self.transform( -3*self.TickLen, n*dY)
        self.xtdiagCnvs.create_text( (x0, y0), fill=self.Achsenfarbe, text=self.YAchsentext )
        
    def draw(self):           
        self.xtdiagCnvs = tk.Canvas(self, bg=self.BackColor, relief=tk.SUNKEN, width=self.Win_X, height=self.Win_Y)
        self.xtdiagCnvs.bind('<Button-1>', self.cllbck)
        self.drawAchses()
        self.drawTicks()
        self.xtdiagCnvs.pack()

    def drawNewValue(self, newPhysX, newPhysY):
        (x0, y0) = self.transformPhystoLogic(self.LastPhysX, self.LastPhysY)
        (x1, y1) = self.transformPhystoLogic(newPhysX, newPhysY)
        (self.LastPhysX, self.LastPhysY) = (newPhysX, newPhysY)
        self.xtdiagCnvs.create_line( ((x0, y0), (x1, y1)), fill='yellow', width=2 )
    
        
if __name__ == "__main__":
    import random
    
    root=tk.Tk()
    gui = XtDiagram(root)
    gui.pack()
    gui.LastPhysX = 0
    gui.LastPhysY = random.gauss(40.0, 0.5)
    dx = 0.5
    x = 0.0
    while ( x<gui.XTicks*gui.PhysX_TickUnit):
        y=random.gauss(40.0, 0.5)
        x += dx
        gui.drawNewValue(x,y) 
    
    root.mainloop()
