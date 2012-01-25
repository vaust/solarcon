'''
Created on 10.01.2012

@author: stegmv
'''

# -*- coding: utf-8 -*-

import tkinter as tk
import tkinter.ttk as ttk

import gui_overview
import gui_FB

import telnetIf

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

guiAll = gui_overview.GuiOverview(nbook.ALL)
guiAll.pack()

guiFB = gui_FB.GuiFB(nbook.FB)
guiFB.pack()

iF = telnetIf.TelnetInterface('192.168.2.102', 1969, 10)
iF.ErmittleMesswerte()
guiAll.updateLabels(iF.t_dict, iF.pu_dict, iF.mv_dict, iF.di_dict, iF.cnt_dict, iF.av_dict)
guiFB.updateLabels(iF.t_dict)

root.mainloop()
