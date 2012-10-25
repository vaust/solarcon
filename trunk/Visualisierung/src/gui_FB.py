'''
Created on 24.01.2012

@author: stegmv
'''
import tkinter as tk
import tkinter.ttk as ttk
import sub_gui_regler

PD = 5
HFARBE  = 'LightGoldenrod1'

class GuiFB(tk.Frame):
    def __init__(self, master=None, 
                 MvReglerParamSchreiben =None,
                 MvReglerParamLesen     =None,
                 schalte_PrimPumpe      =None,
                 schalte_SekPumpe       =None,
                 wechsle_HandAuto       =None,
                 leseMischventil        =None,
                 schreibeMischventil    =None ):
        self.SCHRIFT = ('Arial', 12, 'bold')
        # self.SCHRIFT = ('Arial', 11)
        
        tk.Frame.__init__(self, master)
        self.draw()
         
        self.schalte_PrimPumpe      = schalte_PrimPumpe     
        self.schalte_SekPumpe       = schalte_SekPumpe      
        self.wechsle_HandAuto       = wechsle_HandAuto      
        self.leseMischventil        = leseMischventil       
        self.schreibeMischventil    = schreibeMischventil
        
        self.MvRegler = sub_gui_regler.GuiRegler(self, lf_Name="Mischventilregler")
        self.MvRegler.ParamSchreiben = MvReglerParamSchreiben
        self.MvRegler.ParamLesen     = MvReglerParamLesen
        self.MvRegler.pack()
        
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
                                    variable=self.lf_Process.fb_PrimPumpe_state_tkbl, state=tk.ACTIVE,
                                    command=self.PrimPumpe_changed)
        self.lf_Process.fb_PrimPumpe_chkbttn.grid(column=1, row=0, padx=PD, pady=PD, sticky=tk.NW)

        '''  Checkbutton fuer Sekundärpumpe ein/aus '''
        self.lf_Process.fb_SekPumpe_state_tkbl = tk.BooleanVar()
        self.lf_Process.fb_SekPumpe_chkbttn = ttk.Checkbutton(self.lf_Process, text='Sekundärpumpe ein/aus',
                                    variable=self.lf_Process.fb_SekPumpe_state_tkbl, state=tk.ACTIVE,
                                    command=self.SekPumpe_changed)
        self.lf_Process.fb_SekPumpe_chkbttn.grid(column=1, row=1, padx=PD, pady=PD, sticky=tk.NW)
    
        '''   Mschventilstellung '''
        self.lf_Process.fb_Mischventil_lbl1 = tk.Label(self.lf_Process, text='Mischventilstellung in %:')
        self.lf_Process.fb_Mischventil_lbl1.grid( column=0, row=2, padx=PD, pady=PD, sticky=tk.SW) 
        self.lf_Process.fb_Mischventil_entry = tk.Entry(self.lf_Process, width=12, bg='white')
        self.lf_Process.fb_Mischventil_entry.grid( column=1, row=2, padx=PD, pady=PD, sticky=tk.S)
        self.lf_Process.fb_Mischventil_scle = tk.Scale(self.lf_Process, orient=tk.HORIZONTAL, 
                                    from_=0.0, to=100.0, length=300, resolution=0, state=tk.ACTIVE)
        self.lf_Process.fb_Mischventil_scle.grid(column=2, row=2, columnspan=3, padx=PD, pady=PD) # , sticky=tk.NW)

        self.lf_Process.fb_Mischventil_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Mischventil)
        self.lf_Process.fb_Mischventil_entry.bind('<Return>', self.SetScleVal_Mischventil)
        
        ''' Temperatur Sekundärkreislauf '''
        self.lf_Process.Info1_lbl = tk.Label(self.lf_Process, text='Prim. Rücklauftemp.:')
        self.lf_Process.Info1_lbl.grid(column=2, row=0, padx=PD, pady=PD, sticky=tk.NW)
        self.lf_Process.SekTvlMw_lbl = tk.Label(self.lf_Process, relief='sunken', width=8, bg=HFARBE, 
                                                font=self.SCHRIFT, text='---.-°C')
        self.lf_Process.SekTvlMw_lbl.grid(column=3, row=0, padx=PD, pady=PD, sticky=tk.NW)

        ''' Temperatur Primärkreislauf '''
        self.lf_Process.Info2_lbl = tk.Label(self.lf_Process, text='Sek. Vorlauftemp.:')
        self.lf_Process.Info2_lbl.grid(column=2, row=1, padx=PD, pady=PD, sticky=tk.NW)
        self.lf_Process.PrimTrlMw_lbl = tk.Label(self.lf_Process, relief='sunken', width=8, bg=HFARBE, 
                                                 font=self.SCHRIFT, text='---.-°C')
        self.lf_Process.PrimTrlMw_lbl.grid(column=3, row=1, padx=PD, pady=PD, sticky=tk.NW)
    
    def SetEntryVal_Mischventil(self, event):
        value = self.lf_Process.fb_Mischventil_scle.get()
        self.schreibeMischventil(value)
        s = str(value)[0:6]
        self.lf_Process.fb_Mischventil_entry.delete(0,tk.END)
        self.lf_Process.fb_Mischventil_entry.insert(0, s)
    
    def SetScleVal_Mischventil(self, event):
        value = self.lf_Process.fb_Mischventil_entry.get()
        self.schreibeMischventil(value)
        self.lf_Process.fb_Mischventil_scle.set(value)
               
    def SekPumpe_changed(self):
        self.schalte_SekPumpe( self.lf_Process.fb_SekPumpe_state_tkbl.get() )
    
    def PrimPumpe_changed(self):
        self.schalte_PrimPumpe( self.lf_Process.fb_PrimPumpe_state_tkbl.get() )
    
    def procHandAuto(self):
        if (self.lf_Process.fb_hand_state_tkbl.get() == True):
            '''
            self.lf_Process.fb_PrimPumpe_chkbttn.config(state=tk.ACTIVE)
            self.lf_Process.fb_SekPumpe_chkbttn.config(state=tk.ACTIVE)
            self.lf_Process.fb_Mischventil_scle.config(state=tk.ACTIVE)
            '''
            self.wechsle_HandAuto(True)
        else:
            '''
            self.lf_Process.fb_PrimPumpe_chkbttn.config(state=tk.DISABLED)
            self.lf_Process.fb_SekPumpe_chkbttn.config(state=tk.DISABLED)
            self.lf_Process.fb_Mischventil_scle.config(state=tk.DISABLED)
            '''
            self.wechsle_HandAuto(False)
            
        
    def draw(self):
        self.draw_lf_Process()

    def updateLabels(self, t, mv, pu  ):
        self.lf_Process.PrimTrlMw_lbl.config(text=str(t['FB_PRIM_Trl_MW'])+' °C')
        self.lf_Process.SekTvlMw_lbl.config(text=str(t['FB_SEK_Tvl_MW'])+' °C')
        self.lf_Process.fb_Mischventil_scle.set( float(mv['FB_PRIM_MV_Y']))
        self.lf_Process.fb_Mischventil_entry.delete(0,tk.END)
        self.lf_Process.fb_Mischventil_entry.insert(0,str(mv['FB_PRIM_MV_Y']))
        if (pu['FB_PRIM_PU_SB'].find('EIN') > 0 ):
            self.lf_Process.fb_PrimPumpe_state_tkbl.set(True)
        else:
            self.lf_Process.fb_PrimPumpe_state_tkbl.set(False)
        if ( pu['FB_SEK_PU_SB'].find('EIN') > 0 ):
            self.lf_Process.fb_SekPumpe_state_tkbl.set(True)
        else:
            self.lf_Process.fb_SekPumpe_state_tkbl.set(False)
        
        

#--------------------


if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiFB(root)
    gui.pack()
    root.mainloop()
    
