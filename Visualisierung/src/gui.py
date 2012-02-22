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
import gui_WW

import telnetIf
# import main
import time
import sys

PD = 2

root=tk.Tk()
nbook      = ttk.Notebook(root)
nbook.ALL  = ttk.Frame(nbook)
nbook.SOL  = ttk.Frame(nbook)
nbook.WW   = ttk.Frame(nbook)
nbook.FB   = ttk.Frame(nbook)
nbook.HK   = ttk.Frame(nbook)
nbook.KES  = ttk.Frame(nbook)
nbook.ERR  = ttk.Frame(nbook)
nbook.PAR  = ttk.Frame(nbook)
nbook.ZEIT = ttk.Frame(nbook)
nbook.add(nbook.ALL,  text='Gesamtübersicht')
nbook.add(nbook.SOL,  text='Solarheizkreis')
nbook.add(nbook.WW,   text='Warmwasser')
nbook.add(nbook.FB,   text='Fußbodenheizung')
nbook.add(nbook.HK,   text='Heizkörperheizung')
nbook.add(nbook.KES,  text='Kesselsteuerung')
nbook.add(nbook.ERR,  text='Störungsmeldungen')
nbook.add(nbook.PAR,  text='Parameter')
nbook.add(nbook.ZEIT, text='Zeitprogramm')
nbook.pack(padx=PD, pady=PD, fill=tk.X)

guiAll = gui_overview.GuiOverview(nbook.ALL)
guiAll.pack()

guiFB = gui_FB.GuiFB(nbook.FB)
guiFB.pack()

guiParam = gui_Param.GuiParam(nbook.PAR)
guiParam.pack()

guiWW = gui_WW.GuiWW(nbook.WW)
guiWW.pack( padx=PD, pady=PD )

servernameLbl   = tk.Label(root, text='Servername:')
servernameEntry = tk.Entry(root, width=32, bg='white')
# servernameEntry.insert(0, '192.168.3.33')
servernameEntry.insert(0, 'stegmann.homelinux.org')

def connect():
    global iF
    srvname = servernameEntry.get()
    try:
        iF = telnetIf.TelnetInterface(srvname, 1969, 10)
        # Interface initialisieren
        guiFB.MvReglerParamSchreiben = iF.Fb_MvReglerParamSchreiben
        guiFB.MvReglerParamLesen     = iF.Fb_MvReglerParamLesen
        guiParam.getParam            = iF.Param_GetParam
        guiParam.putParam            = iF.Param_PutParam
        guiWW.PuReglerParamSchreiben = iF.WW_PuReglerParamSchreiben
        guiWW.PuReglerParamLesen     = iF.WW_PuReglerParamLesen
        guiWW.TempLesen              = iF.get_T
        guiWW.t0                     = time.time()
        guiWW.xt1.LastPhysX          = 0
        guiWW.xt2.LastPhysX          = 0
        guiWW.xt1.LastPhysY          = 40.0
        guiWW.xt2.LastPhysY          = 50.0
        
        updateBtn.config(state=tk.ACTIVE)
        disconnectBtn.config(state=tk.ACTIVE)
        connectBtn.config(state=tk.DISABLED)
        servernameEntry.config(state=tk.DISABLED)
    except:
        pass
    
def update():
    global iF
    try:
        iF.ErmittleMesswerte()
        guiAll.updateLabels(iF.t, iF.pu, iF.mv, iF.di, iF.cnt, iF.av)
        guiFB.updateLabels(iF.t)
        guiWW.plot_MW(iF.t, iF.mv)
    except:
        pass
    nbook.after_id = nbook.after(2500,update) # rekursiver Aufruf!
    
def disconnect():
    global iF, after_id
    updateBtn.config(state=tk.DISABLED)
    disconnectBtn.config(state=tk.DISABLED)
    connectBtn.config(state=tk.ACTIVE)
    servernameEntry.config(state=tk.NORMAL)
    try:
        iF.beenden()
        iF.close()
    except:
        pass
    nbook.after_cancel(nbook.after_id)
    
def beenden():
    global iF
    try:
        iF.beenden()
        iF.close()
    except:
        pass
    
    sys.exit()
    

updateBtn = tk.Button(root, text='Messwerte aktualisieren', command=update)
connectBtn = tk.Button(root, text='Verbinden', command=connect)
disconnectBtn = tk.Button(root, text='Verbindung trennen', command=disconnect)
disconnectBtn.config(state=tk.DISABLED)
updateBtn.config(state=tk.DISABLED)
quitBtn = tk.Button(root, text='Beenden', command=beenden)

servernameLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
servernameEntry.pack( padx=PD, pady=PD, side=tk.LEFT )
connectBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
disconnectBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
quitBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
updateBtn.pack( padx=PD, pady=PD, side=tk.RIGHT )
 
root.mainloop()
