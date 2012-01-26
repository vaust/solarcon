'''
Created on 24.01.2012

@author: stegmv
'''
import tkinter as tk
import tkinter.ttk as ttk

PD = 5
HFARBE  = 'LightGoldenrod1'

class GuiFB(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.draw()
        self.MvReglerParamSchreiben = None
        self.MvReglerParamLesen = None
        
    def draw_lf_Process(self):
        ''' Labelframe fuer Prozesssteuerung ''' 
        self.lf_Process = tk.LabelFrame( self, text='Prozesssteuerung')
        self.lf_Process.pack(padx=PD, pady=PD, side=tk.TOP)

        ''' Checkbutton fuer Hand/Auto Eingabe des Reglers 
        self.lf_Process.handin_state_tkbl = tk.BooleanVar()
        self.lf_Process.handin_chkbttn = ttk.Checkbutton(self.lf_Process, text='Prozesseingabe auf Handbetrieb',
                                    variable=self.lf_Process.handin_state_tkbl)
        self.lf_Process.handin_chkbttn.grid(column=0, row=0, padx=PD, pady=PD, sticky=tk.NW)
        '''
        ''' Checkbutton fuer Hand/Autobetrieb des Reglers '''
        self.lf_Process.fb_hand_state_tkbl = tk.BooleanVar()
        self.lf_Process.fb_hand_chkbttn = ttk.Checkbutton(self.lf_Process, text='Prozess auf Handbetrieb',
                                    variable=self.lf_Process.fb_hand_state_tkbl)
        self.lf_Process.fb_hand_chkbttn.grid(column=0, row=1, padx=PD, pady=PD, sticky=tk.NW)
        self.lf_Process.fb_hand_chkbttn.config(command=self.procHandAuto)
        
        ''' Checkbutton fuer Primaerpumpe ein/aus '''
        self.lf_Process.fb_PrimPumpe_state_tkbl = tk.BooleanVar()
        self.lf_Process.fb_PrimPumpe_chkbttn = ttk.Checkbutton(self.lf_Process, text='Primärpumpe ein/aus',
                                    variable=self.lf_Process.fb_PrimPumpe_state_tkbl, state=tk.DISABLED)
        self.lf_Process.fb_PrimPumpe_chkbttn.grid(column=1, row=0, padx=PD, pady=PD, sticky=tk.NW)

        '''  Checkbutton fuer Sekundärpumpe ein/aus '''
        self.lf_Process.fb_SekPumpe_state_tkbl = tk.BooleanVar()
        self.lf_Process.fb_SekPumpe_chkbttn = ttk.Checkbutton(self.lf_Process, text='Sekundärpumpe ein/aus',
                                    variable=self.lf_Process.fb_SekPumpe_state_tkbl, state=tk.DISABLED)
        self.lf_Process.fb_SekPumpe_chkbttn.grid(column=1, row=1, padx=PD, pady=PD, sticky=tk.NW)
    
        '''   Mschventilstellung '''
        self.lf_Process.fb_Mischventil_lbl1 = tk.Label(self.lf_Process, text='Mischventilstellung in %:')
        self.lf_Process.fb_Mischventil_lbl1.grid( column=0, row=2, padx=PD, pady=PD, sticky=tk.SW) 
        self.lf_Process.fb_Mischventil_entry = tk.Entry(self.lf_Process, width=12, bg='white')
        self.lf_Process.fb_Mischventil_entry.grid( column=1, row=2, padx=PD, pady=PD, sticky=tk.S)
        self.lf_Process.fb_Mischventil_scle = tk.Scale(self.lf_Process, orient=tk.HORIZONTAL, 
                                    from_=0.0, to=100.0, length=300, resolution=0, state=tk.DISABLED)
        self.lf_Process.fb_Mischventil_scle.grid(column=2, row=2, columnspan=3, padx=PD, pady=PD) # , sticky=tk.NW)

        self.lf_Process.fb_Mischventil_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Mischventil)
        self.lf_Process.fb_Mischventil_entry.bind('<Return>', self.SetScleVal_Mischventil)
        
        ''' Temperatur Sekundärkreislauf '''
        self.lf_Process.Info1_lbl = tk.Label(self.lf_Process, text='Prim. Rücklauftemp.:')
        self.lf_Process.Info1_lbl.grid(column=2, row=0, padx=PD, pady=PD, sticky=tk.NW)
        self.lf_Process.SekTvlMw_lbl = tk.Label(self.lf_Process, relief='sunken', width=8, bg=HFARBE, text='---.-°C')
        self.lf_Process.SekTvlMw_lbl.grid(column=3, row=0, padx=PD, pady=PD, sticky=tk.NW)

        ''' Temperatur Primärkreislauf '''
        self.lf_Process.Info2_lbl = tk.Label(self.lf_Process, text='Sek. Vorlauftemp.:')
        self.lf_Process.Info2_lbl.grid(column=2, row=1, padx=PD, pady=PD, sticky=tk.NW)
        self.lf_Process.PrimTrlMw_lbl = tk.Label(self.lf_Process, relief='sunken', width=8, bg=HFARBE, text='---.-°C')
        self.lf_Process.PrimTrlMw_lbl.grid(column=3, row=1, padx=PD, pady=PD, sticky=tk.NW)
    
    def SetEntryVal_Mischventil(self, event):
        s = str(self.lf_Process.fb_Mischventil_scle.get())[0:6]
        self.lf_Process.fb_Mischventil_entry.delete(0,tk.END)
        self.lf_Process.fb_Mischventil_entry.insert(0, s)
    
    def SetScleVal_Mischventil(self, event):
        s = self.lf_Process.fb_Mischventil_entry.get()
        self.lf_Process.fb_Mischventil_scle.set(s)
               
    def procHandAuto(self):
        if (self.lf_Process.fb_hand_state_tkbl.get() == True):
            self.lf_Process.fb_PrimPumpe_chkbttn.config(state=tk.ACTIVE)
            self.lf_Process.fb_SekPumpe_chkbttn.config(state=tk.ACTIVE)
            self.lf_Process.fb_Mischventil_scle.config(state=tk.ACTIVE)
        else:
            self.lf_Process.fb_PrimPumpe_chkbttn.config(state=tk.DISABLED)
            self.lf_Process.fb_SekPumpe_chkbttn.config(state=tk.DISABLED)
            self.lf_Process.fb_Mischventil_scle.config(state=tk.DISABLED)
            
    def MvReglerParameter_set(self):
        kp = float(self.lf_mvregler.Kp_entry.get())
        ki = float(self.lf_mvregler.Ki_entry.get())
        ap = float(self.lf_mvregler.AP_entry.get())
        self.MvReglerParamSchreiben(kp, ki, ap)
    
    def MvReglerParameter_get(self):
        (kp, ki, ap) = self.MvReglerParamLesen()
        self.lf_mvregler.Kp_scle.set(kp)
        self.lf_mvregler.Ki_scle.set(ki)
        self.lf_mvregler.AP_scle.set(ap)
        self.lf_mvregler.Kp_entry.delete(0,tk.END)
        self.lf_mvregler.Kp_entry.insert(0, kp)
        self.lf_mvregler.Ki_entry.delete(0,tk.END)
        self.lf_mvregler.Ki_entry.insert(0, ki)
        self.lf_mvregler.AP_entry.delete(0,tk.END)
        self.lf_mvregler.AP_entry.insert(0, ap)
            
    def draw_lf_MvRegler(self):
        ''' FB Mischventilregler parametrieren '''
        self.lf_mvregler = tk.LabelFrame( self, text='Mischventilregler Online Parametrierung')
        self.lf_mvregler.pack(padx=PD, pady=PD, side=tk.TOP)
    
        self.lf_mvregler.Kp_lbl = tk.Label(self.lf_mvregler, text='Proportionalbeiwert Kp:')
        self.lf_mvregler.Kp_entry = tk.Entry(self.lf_mvregler, width=8, bg='white')
        self.lf_mvregler.KpUnit_lbl = tk.Label(self.lf_mvregler, text='%/K')
    
        self.lf_mvregler.Ki_lbl = tk.Label(self.lf_mvregler, text='Integralbeiwert Ki:')
        self.lf_mvregler.Ki_entry = tk.Entry(self.lf_mvregler, width=8, bg='white')
        self.lf_mvregler.KiUnit_lbl = tk.Label(self.lf_mvregler, text='%/(K x sec)')

        self.lf_mvregler.AP_lbl = tk.Label(self.lf_mvregler, text='Arbeitspunkt AP:')
        self.lf_mvregler.AP_entry = tk.Entry(self.lf_mvregler, width=8, bg='white')
        self.lf_mvregler.APUnit_lbl = tk.Label(self.lf_mvregler, text='%')

        self.lf_mvregler.Kp_scle = tk.Scale(self.lf_mvregler, orient=tk.HORIZONTAL, 
                                            from_=0.0, to= 20.0, length=300, resolution=0.01)
        self.lf_mvregler.Ki_scle = tk.Scale(self.lf_mvregler, orient=tk.HORIZONTAL, 
                                            from_=0.0, to= 5.0, length=300, resolution=0.001)
        self.lf_mvregler.AP_scle = tk.Scale(self.lf_mvregler, orient=tk.HORIZONTAL, 
                                            from_=0.0, to=100.0, length=300, resolution=0.1)

        self.lf_mvregler.Kp_lbl.grid(column=0, row=0, padx=PD, sticky=tk.W )
        self.lf_mvregler.Ki_lbl.grid(column=0, row=1, padx=PD, sticky=tk.W )
        self.lf_mvregler.AP_lbl.grid(column=0, row=2, padx=PD, sticky=tk.W )
        self.lf_mvregler.Kp_entry.grid(column=1, row=0, padx=PD )
        self.lf_mvregler.Ki_entry.grid(column=1, row=1, padx=PD )
        self.lf_mvregler.AP_entry.grid(column=1, row=2, padx=PD )
        self.lf_mvregler.KpUnit_lbl.grid(column=2, row=0, padx=PD, sticky=tk.W )
        self.lf_mvregler.KiUnit_lbl.grid(column=2, row=1, padx=PD, sticky=tk.W )
        self.lf_mvregler.APUnit_lbl.grid(column=2, row=2, padx=PD, sticky=tk.W )
        self.lf_mvregler.Kp_scle.grid(column=3, row=0, padx=PD )
        self.lf_mvregler.Ki_scle.grid(column=3, row=1, padx=PD )
        self.lf_mvregler.AP_scle.grid(column=3, row=2, padx=PD )

        self.lf_mvregler.ReadBttn = tk.Button(self.lf_mvregler, text='Lesen',
                                              command=self.MvReglerParameter_get)
        self.lf_mvregler.ChangeBttn = tk.Button(self.lf_mvregler, text='Schreiben', 
                                                command=self.MvReglerParameter_set)
        self.lf_mvregler.ReadBttn.grid(column=2, row=3, padx=PD, pady=PD )
        self.lf_mvregler.ChangeBttn.grid(column=3, row=3, padx=PD, pady=PD )

        
        self.lf_mvregler.Kp_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Kp)
        self.lf_mvregler.Ki_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Ki)
        self.lf_mvregler.AP_scle.bind('<ButtonRelease-1>', self.SetEntryVal_AP)
        self.lf_mvregler.Kp_entry.bind('<Return>', self.SetScleVal_Kp)
        self.lf_mvregler.Ki_entry.bind('<Return>', self.SetScleVal_Ki)
        self.lf_mvregler.AP_entry.bind('<Return>', self.SetScleVal_AP)

    def SetEntryVal_Kp(self, event):
        s = str(self.lf_mvregler.Kp_scle.get())[0:6]
        self.lf_mvregler.Kp_entry.delete(0,tk.END)
        self.lf_mvregler.Kp_entry.insert(0, s)

    def SetEntryVal_Ki(self, event):
        s = str(self.lf_mvregler.Ki_scle.get())[0:6]
        self.lf_mvregler.Ki_entry.delete(0,tk.END)
        self.lf_mvregler.Ki_entry.insert(0, s)

    def SetEntryVal_AP(self, event):
        s = str(self.lf_mvregler.AP_scle.get())[0:6]
        self.lf_mvregler.AP_entry.delete(0,tk.END)
        self.lf_mvregler.AP_entry.insert(0, s)
    
    def SetScleVal_Kp(self, event):
        s = self.lf_mvregler.Kp_entry.get()
        self.lf_mvregler.Kp_scle.set(s)

    def SetScleVal_Ki(self, event):
        s = self.lf_mvregler.Ki_entry.get()
        self.lf_mvregler.Ki_scle.set(s)

    def SetScleVal_AP(self, event):
        s = self.lf_mvregler.AP_entry.get()
        self.lf_mvregler.AP_scle.set(s)

    def draw(self):
        self.draw_lf_Process()
        self.draw_lf_MvRegler()

    def updateLabels(self, t_dict):
        self.lf_Process.PrimTrlMw_lbl.config(text=str(t_dict['FB_PRIM_Trl_MW'])+' °C')
        self.lf_Process.SekTvlMw_lbl.config(text=str(t_dict['FB_SEK_Tvl_MW'])+' °C')
    


if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiFB(root)
    gui.pack()
    root.mainloop()
    
