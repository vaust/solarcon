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
        self.zaehler = 0
        self.draw()
        
        
    def draw(self):
        self.command_lbl   = tk.Label(self, text="Befehl: ")
        self.command_entry = tk.Entry(self, width=64, bg='white')
        self.command_bttn  = tk.Button(self, text='Befehl senden', command=self.druckeAusgabe)
        self.vbar          = ttk.Scrollbar( self, orient=tk.VERTICAL)
        self.text_window   = tk.Text(self, width=100, height=32, yscrollcommand=self.vbar.set)
        
        self.vbar.config(command=self.text_window.yview)
        
        self.command_lbl.grid(column=0, row=0, padx=PD, pady=PD )
        self.command_entry.grid(column=1, row=0, padx=PD, pady=PD )
        self.command_bttn.grid(column=2, row=0, padx=PD, pady=PD )
        self.text_window.grid(column=0, row=1, padx=PD, pady=PD, columnspan=3 )
        self.vbar.grid(column=3, row=1, sticky=tk.NS)
        

    def druckeAusgabe(self):
        self.zaehler += 1
        cmd = self.command_entry.get()
        lines = self.exec_command( cmd.encode('utf8') )
        self.text_window.insert(tk.END, '\n[- '+str(self.zaehler)+' -] :\n')
        for line in lines:
            self.text_window.insert(tk.END, line+'\n')
        self.text_window.yview(tk.END)
        
if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiText(root)
    gui.pack()
    root.mainloop()
    
    