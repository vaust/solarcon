'''
Created on 10.02.2012

@author: stegmv
'''

import tkinter as tk
# import tkinter.ttk as ttk

import xt_Diagram
import sub_gui_regler
import time
import math

PD = 5
HFARBE  = 'LightGoldenrod1'
__DEBUG__ = True

class GuiWW(tk.Frame):
    def __init__(self, master=None,
                       PuReglerParamLesen = None,    
                       PuReglerParamSchreiben = None,
                       TempLesen = None               ):
        tk.Frame.__init__(self, master )
        self.PuReglerParamLesen     = PuReglerParamLesen
        self.PuReglerParamSchreiben = PuReglerParamSchreiben
        self.TempLesen              = TempLesen     
        
        self.xt1 = xt_Diagram.XtDiagram(master, physY_Offs=30, yTicks=5, physY_TickUnit=5, 
                                       yAchsentext='°C', win_Y=150, xTicks=12, physX_TickUnit=10 )
        self.xt2 = xt_Diagram.XtDiagram(master, physY_Offs=0, yTicks=6, physY_TickUnit=20,
                                        yAchsentext='%', win_Y=150, xTicks=12, physX_TickUnit=10 )
        self.xt1.LastPhysX = 0.0
        self.xt1.LastPhysY = 0.0
        self.xt1.LastPhysX = 0.0
        self.xt1.LastPhysY = 0.0
        self.t0 = time.time()
        self.xt1.pack(padx=PD, pady=PD)
        self.xt2.pack(padx=PD, pady=PD)
 
        self.PuRegler = sub_gui_regler.GuiRegler(self, lf_Name="Heizungspumpenregler", Kp_To=25.0)
        self.PuRegler.ParamSchreiben = PuReglerParamSchreiben
        self.PuRegler.ParamLesen     = PuReglerParamLesen
        self.PuRegler.pack()
        
       

    #-------------------- Interface zu xt-Diagramm
    
    def plot_MW(self, temp, pu):
        yt=temp["WW_Tww_MW"] # + 40.0 # zum Testen
        yp=pu["WW_HZG_PU_Y"]
            
        x=time.time()-self.t0
        self.xt1.drawNewValue(x,yt)
        self.xt2.drawNewValue(x,yp)
        x_ultimo = (self.xt1.XTicks-1)*self.xt1.PhysX_TickUnit+self.xt1.PhysX_Offs 
        if ( x > x_ultimo ):
            x_shift = math.ceil( (x-x_ultimo)/self.xt1.PhysX_TickUnit ) * self.xt1.PhysX_TickUnit
            self.xt1.moveChart(-x_shift)
            self.xt2.moveChart(-x_shift)
             
            
if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiWW(root)
    gui.pack()
    root.mainloop()

