'''
Created on 10.02.2012

@author: stegmv
'''

import tkinter as tk
# import tkinter.ttk as ttk

import xt_Diagram
import time
# from threading import Timer

PD = 5
HFARBE  = 'LightGoldenrod1'

class GuiWW(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.PuReglerParamLesen = None
        self.PuReglerParamSchreiben = None
        self.TempLesen = None
        
        self.xt = xt_Diagram.XtDiagram(master)
        self.xt.LastPhysX = 0.0
        self.xt.LastPhysY = 0.0
        self.t0 = time.time()
        
        self.draw()
        
    def draw(self):
        self.xt.pack(padx=PD, pady=PD)

        ''' WW Heizungspumpenregler parametrieren '''
        self.lf_pu_regler = tk.LabelFrame( self, text='Heizungspumpenregler Online Parametrierung')
        self.lf_pu_regler.pack(padx=PD, pady=PD, side=tk.TOP)
        self.lf_pu_regler.Kp_lbl = tk.Label(self.lf_pu_regler, text='Proportionalbeiwert Kp:')
        self.lf_pu_regler.Kp_entry = tk.Entry(self.lf_pu_regler, width=8, bg='white')
        self.lf_pu_regler.KpUnit_lbl = tk.Label(self.lf_pu_regler, text='%/K')
        self.lf_pu_regler.Ki_lbl = tk.Label(self.lf_pu_regler, text='Integralbeiwert Ki:')
        self.lf_pu_regler.Ki_entry = tk.Entry(self.lf_pu_regler, width=8, bg='white')
        self.lf_pu_regler.KiUnit_lbl = tk.Label(self.lf_pu_regler, text='%/(K x sec)')
        self.lf_pu_regler.AP_lbl = tk.Label(self.lf_pu_regler, text='Arbeitspunkt AP:')
        self.lf_pu_regler.AP_entry = tk.Entry(self.lf_pu_regler, width=8, bg='white')
        self.lf_pu_regler.APUnit_lbl = tk.Label(self.lf_pu_regler, text='%')
        self.lf_pu_regler.Kp_scle = tk.Scale(self.lf_pu_regler, orient=tk.HORIZONTAL, 
                                             from_=0.0, to= 50.0, length=300, resolution=0.1)
        self.lf_pu_regler.Ki_scle = tk.Scale(self.lf_pu_regler, orient=tk.HORIZONTAL, 
                                             from_=0.0, to= 20.0, length=300, resolution=0.01)
        self.lf_pu_regler.AP_scle = tk.Scale(self.lf_pu_regler, orient=tk.HORIZONTAL, 
                                             from_=0.0, to=100.0, length=300, resolution=0.1)
        self.lf_pu_regler.Kp_lbl.grid(column=0, row=0, padx=PD, sticky=tk.W )
        self.lf_pu_regler.Ki_lbl.grid(column=0, row=1, padx=PD, sticky=tk.W )
        self.lf_pu_regler.AP_lbl.grid(column=0, row=2, padx=PD, sticky=tk.W )
        self.lf_pu_regler.Kp_entry.grid(column=1, row=0, padx=PD )
        self.lf_pu_regler.Ki_entry.grid(column=1, row=1, padx=PD )
        self.lf_pu_regler.AP_entry.grid(column=1, row=2, padx=PD )
        self.lf_pu_regler.KpUnit_lbl.grid(column=2, row=0, padx=PD, sticky=tk.W )
        self.lf_pu_regler.KiUnit_lbl.grid(column=2, row=1, padx=PD, sticky=tk.W )
        self.lf_pu_regler.APUnit_lbl.grid(column=2, row=2, padx=PD, sticky=tk.W )
        self.lf_pu_regler.Kp_scle.grid(column=3, row=0, padx=PD )
        self.lf_pu_regler.Ki_scle.grid(column=3, row=1, padx=PD )
        self.lf_pu_regler.AP_scle.grid(column=3, row=2, padx=PD )
        self.lf_pu_regler.ReadBttn = tk.Button(self.lf_pu_regler, text='Lesen',
                                               command=self.PuReglerParameter_get)
        self.lf_pu_regler.ChangeBttn = tk.Button(self.lf_pu_regler, text='Schreiben', 
                                                 command=self.PuReglerParameter_set)
        self.lf_pu_regler.ReadBttn.grid(column=2, row=3, padx=PD, pady=PD )
        self.lf_pu_regler.ChangeBttn.grid(column=3, row=3, padx=PD, pady=PD )
        self.lf_pu_regler.Kp_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Kp)
        self.lf_pu_regler.Ki_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Ki)
        self.lf_pu_regler.AP_scle.bind('<ButtonRelease-1>', self.SetEntryVal_AP)
        self.lf_pu_regler.Kp_entry.bind('<Return>', self.SetScleVal_Kp)
        self.lf_pu_regler.Ki_entry.bind('<Return>', self.SetScleVal_Ki)
        self.lf_pu_regler.AP_entry.bind('<Return>', self.SetScleVal_AP)

    def SetEntryVal_Kp(self, event):
        s = str(self.lf_pu_regler.Kp_scle.get())[0:6]
        self.lf_pu_regler.Kp_entry.delete(0,tk.END)
        self.lf_pu_regler.Kp_entry.insert(0, s)

    def SetEntryVal_Ki(self, event):
        s = str(self.lf_pu_regler.Ki_scle.get())[0:6]
        self.lf_pu_regler.Ki_entry.delete(0,tk.END)
        self.lf_pu_regler.Ki_entry.insert(0, s)

    def SetEntryVal_AP(self, event):
        s = str(self.lf_pu_regler.AP_scle.get())[0:6]
        self.lf_pu_regler.AP_entry.delete(0,tk.END)
        self.lf_pu_regler.AP_entry.insert(0, s)
    
    def SetScleVal_Kp(self, event):
        s = self.lf_pu_regler.Kp_entry.get()
        self.lf_pu_regler.Kp_scle.set(s)

    def SetScleVal_Ki(self, event):
        s = self.lf_pu_regler.Ki_entry.get()
        self.lf_pu_regler.Ki_scle.set(s)

    def SetScleVal_AP(self, event):
        s = self.lf_pu_regler.AP_entry.get()
        self.lf_pu_regler.AP_scle.set(s)

    def PuReglerParameter_get(self):
        (kp, ki, ap) = self.PuReglerParamLesen()
        self.lf_pu_regler.Kp_scle.set(kp)
        self.lf_pu_regler.Ki_scle.set(ki)
        self.lf_pu_regler.AP_scle.set(ap)
        self.lf_pu_regler.Kp_entry.delete(0,tk.END)
        self.lf_pu_regler.Kp_entry.insert(0, kp)
        self.lf_pu_regler.Ki_entry.delete(0,tk.END)
        self.lf_pu_regler.Ki_entry.insert(0, ki)
        self.lf_pu_regler.AP_entry.delete(0,tk.END)
        self.lf_pu_regler.AP_entry.insert(0, ap)

    def PuReglerParameter_set(self):
        kp = float(self.lf_pu_regler.Kp_entry.get())
        ki = float(self.lf_pu_regler.Ki_entry.get())
        ap = float(self.lf_pu_regler.AP_entry.get())
        self.PuReglerParamSchreiben(kp, ki, ap)

    #-------------------- Interface zu xt-Diagramm
    
    def plot_Tww_MW(self, temp):
        y=temp["WW_Tww_MW"] + 40.0 # zum Testen
        x=time.time()-self.t0
        self.xt.drawNewValue(x,y)

