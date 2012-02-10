'''
Created on 10.01.2012

@author: stegmv
'''

# -*- coding: utf-8 -*-

import tkinter as tk
import tkinter.ttk as ttk

import gui_overview
import gui_FB
import gui_Param

import telnetIf
# import main
# import time

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
nbook.add(nbook.ALL, text='Gesamtübersicht')
nbook.add(nbook.SOL, text='Solarheizkreis')
nbook.add(nbook.WW, text='Warmwasser')
nbook.add(nbook.FB, text='Fußbodenheizung')
nbook.add(nbook.HK, text='Heizkörperheizung')
nbook.add(nbook.KES, text='Kesselsteuerung')
nbook.add(nbook.ERR, text='Störungsmeldungen')
nbook.add(nbook.PAR, text='Parameter')
nbook.add(nbook.ZEIT, text='Zeitprogramm')
nbook.pack(padx=PD, pady=PD, fill=tk.X)

guiAll = gui_overview.GuiOverview(nbook.ALL)
guiAll.pack()

guiFB = gui_FB.GuiFB(nbook.FB)
guiFB.pack()

guiParam = gui_Param.GuiParam(nbook.PAR)
guiParam.pack()

iF = telnetIf.TelnetInterface('stegmann.homelinux.org', 1969, 10)

# Interface initialisieren
guiFB.MvReglerParamSchreiben = iF.Fb_MvReglerParamSchreiben
guiFB.MvReglerParamLesen = iF.Fb_MvReglerParamLesen
guiParam.getParam = iF.Param_GetParam
guiParam.putParam = iF.Param_PutParam

def update():
    iF.ErmittleMesswerte()
    guiAll.updateLabels(iF.t, iF.pu, iF.mv, iF.di, iF.cnt, iF.av)
    guiFB.updateLabels(iF.t)
    
updateBtn = tk.Button(nbook.ALL, text='Update', command=update)
updateBtn.pack( padx=PD, pady=PD )

root.mainloop()
