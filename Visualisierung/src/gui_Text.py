'''
Created on 27.02.2012

@author: stegmv
'''

import tkinter as tk
import tkinter.ttk as ttk

PD = 5

class GuiText(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.exec_command = None
        self.zaehler    = 0
        self.repeatTime = 5000
        self.cmdlist    = list()
        self.cmdlist.append('help')
        self.draw()
               
    def draw(self):
        self.command_lbl    = tk.Label(self, text="Befehl: ")
        
        self.command_entry  = ttk.Combobox(self, width=64)
        self.command_entry.config( values=self.cmdlist )
        self.command_entry.bind('<Return>', self.Entry_ev)
        
        self.command_bttn   = tk.Button(self, text='Befehl senden', command=self.druckeAusgabe)
        
        self.repeat_state_tkbl = tk.BooleanVar()
        self.repeat_chkbttn = ttk.Checkbutton(self, text='Senden wiederholen an/aus', 
                                              variable=self.repeat_state_tkbl, command=self.Repeat_changed)
        self.vbar          = ttk.Scrollbar( self, orient=tk.VERTICAL)
        self.text_window   = tk.Text(self, width=100, height=30, yscrollcommand=self.vbar.set)
        
        self.vbar.config(command=self.text_window.yview)
        
        self.command_lbl.grid(column=0, row=0, padx=PD, pady=PD)
        self.command_entry.grid(column=1, row=0, padx=PD, pady=PD, sticky=tk.EW)
        self.command_bttn.grid(column=2, row=0, padx=PD, pady=PD)
        self.text_window.grid(column=0, row=1, pady=PD, columnspan=4)
        self.repeat_chkbttn.grid(column=3, row=0, padx=PD, pady=PD)
        self.vbar.grid(column=4, row=1, sticky=tk.NS)
        
    def Entry_ev(self, event):
        self.druckeAusgabe()
        
    def Repeat_changed(self):
        if( self.repeat_state_tkbl.get() == False ):
            self.after_cancel(self.after_id)
        
    def druckeAusgabe(self):
        self.zaehler += 1
        cmd = self.command_entry.get()
        if (self.cmdlist.count(cmd) == 0):
            self.cmdlist.append(cmd)
        self.command_entry.config( values=self.cmdlist )
        lines = self.exec_command( cmd.encode('utf8') )
        self.text_window.insert(tk.END, '\n[- '+str(self.zaehler)+' -] :\n')
        for line in lines:
            self.text_window.insert(tk.END, line+'\n')
        self.text_window.yview(tk.END)
        if( self.repeat_state_tkbl.get() == True ):
            self.after_id=self.after(self.repeatTime, self.druckeAusgabe)
        
if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiText(root)
    gui.pack()
    root.mainloop()
    
    