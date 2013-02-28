'''
Created on 13.02.2012

@author: stegmv
'''

import tkinter as tk

class XtDiagram(tk.Frame):
    def __init__(self, 
                 master          = None,
                 win_X           = 1200,         # Fensterbreite in Pixel
                 win_Y           =  340,         # Fensterhoehe in Pixel
                 win_Xoffset     =   25,         # x-Achsenoffset in Pixel 
                 win_Yoffset     =   20,         # y-Achsenoffset in Pixel     
                 xTicks          =   24,         # Anzahl der x-Achsenabschnitte (am besten gerade!)
                 yTicks          =   20,         # Anzahl der y-Achsenabschnitte
                 tickLen         =    4,         # Achsenabschnittslinienlaenge in Pixel
                 physX_TickUnit  =   60,         # physikalische x-Einheiten pro Achsenabschnitt 
                 physY_TickUnit  =    1,         # physikalische y-Einheiten pro Achsenabschnitt
                 physX_Offs      =    0,         # Startwert der x-Achse 
                 physY_Offs      =   30,         # °C
                 backColor       = 'black',      # Hintergrundfarbe
                 achsenfarbe     = 'green',      # Achsenfarbe
                 gridfarbe       = 'darkgreen',  # 'DarkKhaki' #
                 xAchsentext     = 'sec',        # Einheitenname der x-Achse
                 yAchsentext     = '°C',         # Einheitenname der y-Achse
                 chartWidth      =    2,         # Staerke der Datenlinie
                 chartFarbe      = 'DarkOrange1' # Gitterfarbe
                  ):
        tk.Frame.__init__(self, master, relief=tk.SUNKEN)

        self.Win_X           = win_X         
        self.Win_Y           = win_Y         
        self.Win_Xoffset     = win_Xoffset   
        self.Win_Yoffset     = win_Yoffset   
        self.XTicks          = xTicks        
        self.YTicks          = yTicks        
        self.TickLen         = tickLen       
        self.PhysX_TickUnit  = physX_TickUnit
        self.PhysY_TickUnit  = physY_TickUnit
        self.PhysX_Offs      = physX_Offs    
        self.PhysY_Offs      = physY_Offs    
        self.BackColor       = backColor     
        self.Achsenfarbe     = achsenfarbe   
        self.Gridfarbe       = gridfarbe     
        self.XAchsentext     = xAchsentext   
        self.YAchsentext     = yAchsentext   
        self.ChartWidth      = chartWidth    
        self.ChartFarbe      = chartFarbe    
               
        self.Win_Xspan   = self.Win_X-2*self.Win_Xoffset
        self.Win_Yspan   = self.Win_Y-2*self.Win_Yoffset

        self.LastPhysX   = self.PhysX_Offs
        self.LastPhysY   = self.PhysY_Offs
        
        self.chartline_id = list()
        
        self.draw()

    def cllbck(self, event): 
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
        self.xAchsen_id = self.xtCnvs.create_line( ((x0, y0), (x1, y1)), 
                                                   fill=self.Achsenfarbe, width=1, arrow=tk.LAST )
        # (x0, y0) = self.transform(0, -self.Win_Yoffset)
        (x0, y0) = self.transform(0, -10)
        (x1, y1) = self.transform(0,  self.Win_Yspan  )
        self.yAchsen_id =self.xtCnvs.create_line( ((x0, y0), (x1, y1)), 
                                                  fill=self.Achsenfarbe, width=1, arrow=tk.LAST )
    
    def drawXTicks(self):
        dX = self.Win_Xspan / self.XTicks
        self.xtick_id = list()
        self.xgrid_id = list()
        n = 1
        while( n<self.XTicks):
            (x0, y0) = self.transform(n*dX, -self.TickLen)
            (x1, y1) = self.transform(n*dX, +self.TickLen)
            (x2, y2) = self.transform(n*dX, self.Win_Yspan)
            ident = self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1 )
            self.xtick_id.append(ident)
            ident = self.xtCnvs.create_line( ((x1, y1), (x2, y2)), fill=self.Gridfarbe, width=1 )
            self.xgrid_id.append(ident)
            n += 1

        (x0, y0) = self.transform(n*dX, -3*self.TickLen)
        self.xAchsentext_id = self.xtCnvs.create_text( (x0, y0), fill=self.Achsenfarbe, text=self.XAchsentext )

    def writeXTickstext(self):
        dX = self.Win_Xspan / self.XTicks
        self.xticktext_id = list()
        n = 1
        while( n<self.XTicks):
            (x0, y0) = self.transform(n*dX, -self.TickLen)
            ident = self.xtCnvs.create_text( (x0, y0+2*self.TickLen), fill=self.Achsenfarbe, 
                                         text=str(n*self.PhysX_TickUnit+self.PhysX_Offs))
            self.xticktext_id.append(ident)
            n += 1
            
    def drawYTicks(self):
        dY=  self.Win_Yspan / self.YTicks
        self.ytick_id = list()
        self.yticktext_id = list()
        self.ygrid_id = list()
        n = 1
        while( n<self.YTicks):
            (x0, y0) = self.transform( -self.TickLen, n*dY)
            (x1, y1) = self.transform(  self.TickLen, n*dY)
            (x2, y2) = self.transform(  self.Win_Xspan, n*dY)
            ident = self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.Achsenfarbe, width=1 )
            self.ytick_id.append(ident)
            ident = self.xtCnvs.create_line( ((x1, y1), (x2, y2)), fill=self.Gridfarbe, width=1 )
            self.ygrid_id.append(ident)
            ident = self.xtCnvs.create_text( (x0-2*self.TickLen, y0), fill=self.Achsenfarbe, 
                                         text=str(n*self.PhysY_TickUnit+self.PhysY_Offs))
            self.yticktext_id.append(ident)
            n += 1
   
        (x0, y0) = self.transform( -3*self.TickLen, n*dY)
        self.yAchsentext_id =self.xtCnvs.create_text( (x0, y0), fill=self.Achsenfarbe, text=self.YAchsentext )
        
    def draw(self):           
        PD=2
        self.xtCnvs = tk.Canvas(self, bg=self.BackColor, relief=tk.SUNKEN, width=self.Win_X, height=self.Win_Y)
        self.xtCnvs.bind('<Button-1>', self.cllbck)
        self.drawAchses()
        self.drawXTicks()
        self.writeXTickstext()
        self.drawYTicks()
        self.xtCnvs.pack()
        
        self.xLbl = tk.Label( self, text='Mouse Click: x-Wert: ' )
        self.yLbl = tk.Label( self, text='y-Wert: ' )
        self.xVal = tk.Label( self, width=8, relief=tk.SUNKEN, bg='LightGoldenrod1' )
        self.yVal = tk.Label( self, width=8, relief=tk.SUNKEN, bg='LightGoldenrod1' )
        self.xLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
        self.xVal.pack( padx=PD, pady=PD, side=tk.LEFT )
        self.yLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
        self.yVal.pack( padx=PD, pady=PD, side=tk.LEFT )
    
    def drawNewValue(self, newPhysX, newPhysY):
        (x0, y0) = self.transformPhysToCnvs(self.LastPhysX, self.LastPhysY)
        (x1, y1) = self.transformPhysToCnvs(newPhysX, newPhysY)
        (self.LastPhysX, self.LastPhysY) = (newPhysX, newPhysY)
        ident = self.xtCnvs.create_line( ((x0, y0), (x1, y1)), fill=self.ChartFarbe, width=self.ChartWidth )
        self.chartline_id.append(ident)
        
    def moveChart(self, d_PhysX):
        # x-Achsenbeschriftung löschen:
        for i in self.xticktext_id:
            self.xtCnvs.delete(i) 
        
        # Chartlinie verschieben
        for i in self.chartline_id:
            dx = d_PhysX/self.PhysX_TickUnit *  self.Win_Xspan/self.XTicks 
            self.xtCnvs.move(i, dx, 0)
        
        # x-Achse neu beschriften
        self.PhysX_Offs -= d_PhysX
        self.writeXTickstext()
        
#-------------------
           
if __name__ == "__main__":
    import random
    
    def doit():
        gui.moveChart(-2)
        gui.after(500, doit)
        
    root=tk.Tk()
    gui = XtDiagram(root, win_X=1000, win_Y=400, xTicks=10, physX_TickUnit=10)
    gui.after(500, doit)
    gui.pack()
    gui.LastPhysX = 0
    gui.LastPhysY = random.gauss(40.0, 0.25)
    dx = 0.2
    x  = 0.00
    while ( x<3*gui.XTicks*gui.PhysX_TickUnit ):
        y=random.gauss(40.0, 0.5)
        x += dx
        gui.drawNewValue(x,y) 
    
    # gui.moveChart(-10)
    
    root.mainloop()
