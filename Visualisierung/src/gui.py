'''
Created on 10.01.2012

@author: stegmv
'''

# -*- coding: utf-8 -*-

import tkinter as tk
import tkinter.ttk as ttk
import tkinter.simpledialog as tksimple

import gui_overview
import gui_FB
import gui_Param
import gui_WW
import gui_Text
import telnetIf
import time
import sys
import os

PD = 2

PASSWORT = 'SONNENWASSER'

root=tk.Tk()
root.title('Ruderclub Aschaffenburg Heizungsanlagenbedienung V0.2')
if (os.name.find('nt') >= 0):
    root.iconbitmap('RCA.ico')

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
nbook.TEXT = ttk.Frame(nbook)
nbook.add(nbook.TEXT, text='Text (Telnet)')
nbook.add(nbook.ALL,  text='Anlagengrafik')
nbook.add(nbook.SOL,  text='Solar')
nbook.add(nbook.WW,   text='Warmwasser')
nbook.add(nbook.FB,   text='Fußbodenheizung')
nbook.add(nbook.HK,   text='Heizkörperheizung')
nbook.add(nbook.KES,  text='Kessel')
nbook.add(nbook.ERR,  text='Störungen')
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

guiText = gui_Text.GuiText(nbook.TEXT)
guiText.pack( padx=PD, pady=PD )

servernameLbl   = tk.Label(root, text='Servername:')
serverlist      = ['stegmann.homelinux.org', '192.168.3.33', '192.168.2.104']
servernameEntry = ttk.Combobox(root, width=32, values=serverlist)
passwordLbl     = tk.Label(root, text='Passwort:')
passwordEntry   = tk.Entry(root, width=16, show='*')


def connect():
    global iF
    srvname = servernameEntry.get()
    passwd = passwordEntry.get()
    passwd = passwd.upper() 
    if (passwd.find('SONNENWASSER') >= 0):
        if (serverlist.count(srvname) == 0):
            serverlist.append(srvname)
            serverlist.sort()
            servernameEntry.config( values=serverlist )
    
        try:
            iF = telnetIf.TelnetInterface(srvname, 1969, 30)
            # Interface initialisieren
            guiFB.MvReglerParamSchreiben = iF.Fb_MvReglerParamSchreiben
            guiFB.MvReglerParamLesen     = iF.Fb_MvReglerParamLesen
            guiFB.schalte_PrimPumpe      = iF.Fb_Schalte_PrimPumpe
            guiFB.schalte_SekPumpe       = iF.Fb_Schalte_SekPumpe
            guiFB.wechsle_HandAuto       = iF.Fb_wechsle_HandAuto
            guiFB.leseMischventil        = iF.Fb_leseMischventil
            guiFB.schreibeMischventil    = iF.Fb_schreibeMischventil
    
            guiParam.getParam            = iF.Param_GetParam
            guiParam.putParam            = iF.Param_PutParam
    
            guiWW.PuReglerParamSchreiben = iF.WW_PuReglerParamSchreiben
            guiWW.PuReglerParamLesen     = iF.WW_PuReglerParamLesen
            guiWW.t0                     = time.time()
            guiWW.xt1.LastPhysX          = 0
            guiWW.xt2.LastPhysX          = 0
            guiWW.xt1.LastPhysY          = 40.0
            guiWW.xt2.LastPhysY          = 50.0
    
            guiText.exec_command         = iF.HoleAntwort
            
            connectBtn.config(state=tk.DISABLED)
            servernameEntry.config(state=tk.DISABLED)
    
            # Messwerterfassung starten
            update()
        except:
            pass
    else:
        pass
        
def update():
    global iF
    try:
        iF.ErmittleMesswerte()
        guiAll.updateLabels(iF.t, iF.pu, iF.mv, iF.di, iF.cnt, iF.av)
        guiFB.updateLabels(iF.t, iF.mv, iF.pu)
        guiWW.plot_MW(iF.t, iF.mv)
    except:
        pass
    if( Aktualisieren_state_tkbl.get() == True ):
        nbook.after_id = nbook.after(5000, update) # rekursiver Aufruf!
            
def beenden():
    global iF
    try:
        iF.beenden()
        iF.close()
    except:
        pass
    
    sys.exit()

def Aktualisieren_changed():
    if (Aktualisieren_state_tkbl.get() == True):
        update()
    else:
        nbook.after_cancel(nbook.after_id)
        
connectBtn = tk.Button(root, text='Verbinden', command=connect)
''' Checkbutton fuer Aktualisierung ein/aus '''
Aktualisieren_state_tkbl = tk.BooleanVar()
Aktualisieren_chkbttn = ttk.Checkbutton(root, text='Aktualisieren an/aus', variable=Aktualisieren_state_tkbl,
                                        command=Aktualisieren_changed)
quitBtn = tk.Button(root, text='Beenden', command=beenden)

servernameLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
servernameEntry.pack( padx=PD, pady=PD, side=tk.LEFT )
connectBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
quitBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
Aktualisieren_chkbttn.pack( padx=PD, pady=PD, side=tk.LEFT )
passwordLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
passwordEntry.pack( padx=PD, pady=PD, side=tk.LEFT )

root.mainloop()
