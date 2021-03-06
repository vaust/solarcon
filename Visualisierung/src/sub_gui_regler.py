'''
Created on 16.10.2012

@author: stegmv
'''
import tkinter as tk

PD = 5

class GuiRegler(tk.Frame):

    def __init__(self, master=None, lf_Name=None, 
                 ParamSchreiben=None, ParamLesen=None,
                 Kp_To=20.0, Ki_To=5.0 ):
        tk.Frame.__init__(self, master)
        self.lf_Name = lf_Name
        self.ParamSchreiben = ParamSchreiben
        self.ParamLesen     = ParamLesen
        self.Kp_To = Kp_To
        self.Ki_To = Ki_To            
        self.draw()

        self.SetEntryVal_Kp(0)
        self.SetEntryVal_Ki(0)
        self.SetEntryVal_AP(0)

    def draw(self):
        self.lf_regler = tk.LabelFrame( self, text=self.lf_Name )
        self.lf_regler.pack(padx=PD, pady=PD, side=tk.TOP)
        
        self.lf_regler.Kp_lbl = tk.Label(self.lf_regler, text='Proportionalbeiwert Kp:')
        self.lf_regler.Kp_entry = tk.Entry(self.lf_regler, width=8, bg='white')
        self.lf_regler.KpUnit_lbl = tk.Label(self.lf_regler, text='%/K')
        
        self.lf_regler.Ki_lbl = tk.Label(self.lf_regler, text='Integralbeiwert Ki:')
        self.lf_regler.Ki_entry = tk.Entry(self.lf_regler, width=8, bg='white')
        self.lf_regler.KiUnit_lbl = tk.Label(self.lf_regler, text='%/(K x sec)')
        
        self.lf_regler.AP_lbl = tk.Label(self.lf_regler, text='Arbeitspunkt AP:')
        self.lf_regler.AP_entry = tk.Entry(self.lf_regler, width=8, bg='white')
        self.lf_regler.APUnit_lbl = tk.Label(self.lf_regler, text='%')
        
        self.lf_regler.Kp_scle = tk.Scale(self.lf_regler, orient=tk.HORIZONTAL, 
                                          from_=0.0, to=self.Kp_To, length=300, resolution=0.01)
        self.lf_regler.Ki_scle = tk.Scale(self.lf_regler, orient=tk.HORIZONTAL, 
                                          from_=0.0, to=self.Ki_To, length=300, resolution=0.01)
        self.lf_regler.AP_scle = tk.Scale(self.lf_regler, orient=tk.HORIZONTAL, 
                                          from_=0.0, to=100.0, length=300, resolution=0.1)
        
        self.lf_regler.Kp_lbl.grid(column=0, row=0, padx=PD, sticky=tk.W )
        self.lf_regler.Ki_lbl.grid(column=0, row=1, padx=PD, sticky=tk.W )
        self.lf_regler.AP_lbl.grid(column=0, row=2, padx=PD, sticky=tk.W )
        self.lf_regler.Kp_entry.grid(column=1, row=0, padx=PD )
        self.lf_regler.Ki_entry.grid(column=1, row=1, padx=PD )
        self.lf_regler.AP_entry.grid(column=1, row=2, padx=PD )
        self.lf_regler.KpUnit_lbl.grid(column=2, row=0, padx=PD, sticky=tk.W )
        self.lf_regler.KiUnit_lbl.grid(column=2, row=1, padx=PD, sticky=tk.W )
        self.lf_regler.APUnit_lbl.grid(column=2, row=2, padx=PD, sticky=tk.W )
        self.lf_regler.Kp_scle.grid(column=3, row=0, padx=PD )
        self.lf_regler.Ki_scle.grid(column=3, row=1, padx=PD )
        self.lf_regler.AP_scle.grid(column=3, row=2, padx=PD )
        
        self.lf_regler.ReadBttn = tk.Button(self.lf_regler, text='Lesen',
                                            command=self.ParameterGet)
        self.lf_regler.ChangeBttn = tk.Button(self.lf_regler, text='Schreiben', 
                                              command=self.ParameterSet)
        self.lf_regler.ReadBttn.grid(column=2, row=3, padx=PD, pady=PD )
        self.lf_regler.ChangeBttn.grid(column=3, row=3, padx=PD, pady=PD )
        
        
        self.lf_regler.Kp_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Kp)
        self.lf_regler.Ki_scle.bind('<ButtonRelease-1>', self.SetEntryVal_Ki)
        self.lf_regler.AP_scle.bind('<ButtonRelease-1>', self.SetEntryVal_AP)
        self.lf_regler.Kp_entry.bind('<Return>', self.SetScleVal_Kp)
        self.lf_regler.Ki_entry.bind('<Return>', self.SetScleVal_Ki)
        self.lf_regler.AP_entry.bind('<Return>', self.SetScleVal_AP)

    def SetEntryVal_Kp(self, event):
        s = str(self.lf_regler.Kp_scle.get())[0:6]
        self.lf_regler.Kp_entry.delete(0,tk.END)
        self.lf_regler.Kp_entry.insert(0, s)

    def SetEntryVal_Ki(self, event):
        s = str(self.lf_regler.Ki_scle.get())[0:6]
        self.lf_regler.Ki_entry.delete(0,tk.END)
        self.lf_regler.Ki_entry.insert(0, s)

    def SetEntryVal_AP(self, event):
        s = str(self.lf_regler.AP_scle.get())[0:6]
        self.lf_regler.AP_entry.delete(0,tk.END)
        self.lf_regler.AP_entry.insert(0, s)
    
    def SetScleVal_Kp(self, event):
        s = self.lf_regler.Kp_entry.get()
        self.lf_regler.Kp_scle.set(s)

    def SetScleVal_Ki(self, event):
        s = self.lf_regler.Ki_entry.get()
        self.lf_regler.Ki_scle.set(s)

    def SetScleVal_AP(self, event):
        s = self.lf_regler.AP_entry.get()
        self.lf_regler.AP_scle.set(s)

    def ParameterSet(self):
        kp = float(self.lf_regler.Kp_entry.get())
        ki = float(self.lf_regler.Ki_entry.get())
        ap = float(self.lf_regler.AP_entry.get())
        self.ParamSchreiben(kp, ki, ap)
    
    def ParameterGet(self):
        (kp, ki, ap) = self.ParamLesen()
        self.lf_regler.Kp_scle.set(kp)
        self.lf_regler.Ki_scle.set(ki)
        self.lf_regler.AP_scle.set(ap)
        self.lf_regler.Kp_entry.delete(0,tk.END)
        self.lf_regler.Kp_entry.insert(0, kp)
        self.lf_regler.Ki_entry.delete(0,tk.END)
        self.lf_regler.Ki_entry.insert(0, ki)
        self.lf_regler.AP_entry.delete(0,tk.END)
        self.lf_regler.AP_entry.insert(0, ap)

""" ------------------------------------------------------ """

if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiRegler(root, lf_Name="Hallo")
    gui.pack()
    root.mainloop()
    
    
