'''
Created on 13.02.2012

@author: stegmv
'''

import tkinter as tk

class XtDiagram(tk.Frame):
    Win_X       = 1200
    Win_Y       = 340
    Win_Xoffset = 25
    Win_Yoffset = 20        

    XTicks      = 25
    YTicks      = 20
    TickLen     =  4 
    
    PhysX_TickUnit  = 60   # sec
    PhysY_TickUnit  =  1   # °C
    PhysX_Offs      =  0   # sec
    PhysY_Offs      = 33   # °C

    BackColor   = 'black'
    Achsenfarbe = 'green'
    Gridfarbe   = 'DarkKhaki' # 'darkgreen' #
    XAchsentext = 'sec'
    YAchsentext = '°C'

    ChartWidth  = 2
    ChartFarbe  = 'DarkOrange1'
    
    def __init__(self, master=None):
        tk.Frame.__init__(self, master, relief=tk.SUNKEN)

        self.Win_Xspan   = self.Win_X-2*self.Win_Xoffset
        self.Win_Yspan   = self.Win_Y-2*self.Win_Yoffset

        self.LastPhysX   = self.PhysX_Offs
        self.LastPhysY   = self.PhysY_Offs
        
        self.draw()

    def cllbck(self, event): 
        '''
        todo Umbauen zu Funktion, um Messwerte als Phys Werte aus Diagramm anzuzeigen  
        '''
        (pX, pY) = self.inv_transformPhysToCnvs( self.xtCnvs.canvasx(event.x), self.xtCnvs.canvasy(event.y) ) 
        self.xVal.config( text=str(pX)[0:6] )
        self.yVal.config( text=str(pY)[0:6] )
                                                      
    def transform(self, x, y):
        x1 =  x + self.Win_Xoffset
        y1 = -y + (self.Win_Y-self.Win_Yoffset) 
        return (x1, y1)
    
    def inv_transform(self, x1, y1):
        x = x1 - self.Win_Xoffset
        y = (self.Win_Y-self.Win_Yoffset) - y1
        return (x, y)
    
    def transformPhysToCnvs(self, physX, physY):    
        x1=(physX-self.PhysX_Offs)/self.PhysX_TickUnit * self.Win_Xspan/self.XTicks
        y1=(physY-self.PhysY_Offs)/self.PhysY_TickUnit * self.Win_Yspan/self.YTicks
        (x2, y2) = self.transform(x1, y1)
        return (x2, y2)
    
    def inv_transformPhysToCnvs(self, x2, y2):
        (x1, y1) = self.inv_transform(x2, y2)
        physX = x1 * self.PhysX_TickUnit/self.Win_Xspan*self.XTicks + self.PhysX_Offs
        physY = y1 * self.PhysY_TickUnit/self.Win_Yspan*self.YTicks + self.PhysY_Offs
        return( physX, physY )

    def drawAchses(self):
        # (x0, y0) = self.transform(-self.Win_Xoffset, 0)
        (x0, y0) = self.transform(-10, 0)
        (x1, y1) = self.transform( self.Win_Xspan  , 0) 
        self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1, arrow=tk.LAST )
        # (x0, y0) = self.transform(0, -self.Win_Yoffset)
        (x0, y0) = self.transform(0, -10)
        (x1, y1) = self.transform(0,  self.Win_Yspan  )
        self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1, arrow=tk.LAST )
    
    def drawTicks(self):
        dX = self.Win_Xspan / self.XTicks
        dY=  self.Win_Yspan / self.YTicks
        n = 1
        while( n<self.XTicks):
            (x0, y0) = self.transform(n*dX, -self.TickLen)
            (x1, y1) = self.transform(n*dX, +self.TickLen)
            (x2, y2) = self.transform(n*dX, self.Win_Yspan)
            self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1 )
            self.xtCnvs.create_line( ((x1, y1), (x2, y2)), fill=self.Gridfarbe, width=1 )
            self.xtCnvs.create_text( (x0, y0+2*self.TickLen), fill=self.Achsenfarbe, 
                                         text=str(n*self.PhysX_TickUnit+self.PhysX_Offs))
            n += 1

        (x0, y0) = self.transform(n*dX, -3*self.TickLen)
        self.xtCnvs.create_text( (x0, y0), fill=self.Achsenfarbe, text=self.XAchsentext )
        
        n = 1
        while( n<self.YTicks):
            (x0, y0) = self.transform( -self.TickLen, n*dY)
            (x1, y1) = self.transform(  self.TickLen, n*dY)
            (x2, y2) = self.transform(  self.Win_Xspan, n*dY)
            self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1 )
            self.xtCnvs.create_line( ((x1, y1), (x2, y2)), fill=self.Gridfarbe, width=1 )
            self.xtCnvs.create_text( (x0-2*self.TickLen, y0), fill=self.Achsenfarbe, 
                                         text=str(n*self.PhysY_TickUnit+self.PhysY_Offs))
            n += 1
   
        (x0, y0) = self.transform( -3*self.TickLen, n*dY)
        self.xtCnvs.create_text( (x0, y0), fill=self.Achsenfarbe, text=self.YAchsentext )
        
    def draw(self):           
        self.xtCnvs = tk.Canvas(self, bg=self.BackColor, relief=tk.SUNKEN, width=self.Win_X, height=self.Win_Y)
        self.xtCnvs.bind('<Button-1>', self.cllbck)
        self.drawAchses()
        self.drawTicks()
        self.xtCnvs.pack()
        
        self.xLbl = tk.Label( self, text='Mouse Click: x-Wert: ' )
        self.yLbl = tk.Label( self, text='y-Wert: ' )
        self.xVal = tk.Label( self, width=8, relief=tk.SUNKEN, bg='LightGoldenrod1' )
        self.yVal = tk.Label( self, width=8, relief=tk.SUNKEN, bg='LightGoldenrod1' )
        self.xLbl.pack( padx=5, pady=5, side=tk.LEFT )
        self.xVal.pack( padx=5, pady=5, side=tk.LEFT )
        self.yLbl.pack( padx=5, pady=5, side=tk.LEFT )
        self.yVal.pack( padx=5, pady=5, side=tk.LEFT )
    
    def drawNewValue(self, newPhysX, newPhysY):
        (x0, y0) = self.transformPhysToCnvs(self.LastPhysX, self.LastPhysY)
        (x1, y1) = self.transformPhysToCnvs(newPhysX, newPhysY)
        (self.LastPhysX, self.LastPhysY) = (newPhysX, newPhysY)
        self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.ChartFarbe, width=self.ChartWidth )
    
        
if __name__ == "__main__":
    import random
    
    root=tk.Tk()
    gui = XtDiagram(root)
    gui.pack()
    gui.LastPhysX = 0
    gui.LastPhysY = random.gauss(40.0, 0.25)
    dx = 0.05
    x  = 0.00
    while ( x<gui.XTicks*gui.PhysX_TickUnit ):
        y=random.gauss(40.0, 0.25)
        x += dx
        gui.drawNewValue(x,y) 
    
    root.mainloop()
