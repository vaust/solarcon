'''
Created on 10.01.2012

@author: stegmv
'''

# -*- coding: utf-8 -*-


import tkinter as tk
import tkinter.ttk as ttk

import gui_overview


root=tk.Tk()
PD = 5
nbook = ttk.Notebook(root)
nbook.ALL = ttk.Frame(nbook)
nbook.SOL = ttk.Frame(nbook)
nbook.WW = ttk.Frame(nbook)
nbook.FB = ttk.Frame(nbook)
nbook.HK = ttk.Frame(nbook)
nbook.KES = ttk.Frame(nbook)
nbook.ERR = ttk.Frame(nbook)
nbook.PAR = ttk.Frame(nbook)
nbook.ZEIT = ttk.Frame(nbook)
nbook.add(nbook.ALL, text='Gesamtuebersicht')
nbook.add(nbook.SOL, text='Solarheizkreis')
nbook.add(nbook.WW, text='Warmwasser')
nbook.add(nbook.FB, text='Fussbodenheizung')
nbook.add(nbook.HK, text='Heizkoerperheizung')
nbook.add(nbook.KES, text='Kesselsteuerung')
nbook.add(nbook.ERR, text='Stoerungsmeldungen')
nbook.add(nbook.PAR, text='Parameter')
nbook.add(nbook.ZEIT, text='Zeitprogramm')
nbook.pack(padx=PD, pady=PD, fill=tk.X)

gui = gui_overview.GuiOverview(nbook.ALL)
gui.pack()
gui.pu_lbl["WW_HZG_PU_SB"].config(text='666')
gui.mainloop()
