# -*- coding: utf-8 -*-
'''
Created on 10.01.2012
@author: Volker Stegmann
'''


import tkinter as tk
import tkinter.ttk as ttk

import gui_overview, gui_FB, gui_Param, gui_WW, gui_Text
import telnetIf
import time, sys, hashlib

PD = 2
PASSWORTMD5HASH = '19c7b2a53c6f0b0f6b1a6baf27729bd7'

root=tk.Tk()
root.title('Ruderclub Aschaffenburg Heizungsanlagenbedienung V0.4')
if (sys.platform.startswith('win32')):
    root.iconbitmap('RCA.ico')

'''
books = ('Text (Telnet)', 'Anlagengrafik', 'Solar', 'Warmwasser', 'Fußbodenheizung', 
         'Heizkörperheizung', 'Kessel', 'Störungen', 'Parameter', 'Zeitprogramm' )
'''
books = ('Text (Telnet)', 'Anlagengrafik', 'Warmwasser', 'Fußbodenheizung', 'Kessel', 'Parameter' )    
    
nbook       = ttk.Notebook(root)
nbook.books = dict()

for bk in books:
    nbook.books[bk] = ttk.Frame(nbook)
    nbook.add(nbook.books[bk], text=bk)

nbook.pack(padx=PD, pady=PD, fill=tk.X)

guiAll = gui_overview.GuiOverview(nbook.books['Anlagengrafik'])
guiAll.pack()

servernameLbl   = tk.Label(root, text='Servername:')
serverlist      = ['192.168.2.106', 'stegmann.homelinux.org']
servernameEntry = ttk.Combobox(root, width=32, values=serverlist)
passwordLbl     = tk.Label(root, text='Passwort:')
passwordEntry   = tk.Entry(root, width=16, show='*')

def connect():
    global iface, guiFB, guiWW, guiText, guiParam
    srvname = servernameEntry.get()
    # '''
    passwd = passwordEntry.get()
    h=hashlib.md5()
    h.update(passwd.encode())
    md5hex = h.hexdigest()
    if (md5hex.find(PASSWORTMD5HASH) >= 0):
    # '''
    # if True:
        if (serverlist.count(srvname) == 0):
            serverlist.append(srvname)
            serverlist.sort()
            servernameEntry.config( values=serverlist )
    
        try:
            iface = telnetIf.TelnetInterface(srvname, 1969, 30)
            # GUIs instanzieren und Interfaces initialisieren
            guiFB = gui_FB.GuiFB(nbook.books['Fußbodenheizung'],
                                 MvReglerParamSchreiben = iface.Fb_MvReglerParamSchreiben,
                                 MvReglerParamLesen     = iface.Fb_MvReglerParamLesen,
                                 schalte_PrimPumpe      = iface.Fb_Schalte_PrimPumpe,
                                 schalte_SekPumpe       = iface.Fb_Schalte_SekPumpe,
                                 wechsle_HandAuto       = iface.Fb_wechsle_HandAuto,
                                 leseMischventil        = iface.Fb_leseMischventil,
                                 schreibeMischventil    = iface.Fb_schreibeMischventil )
            guiFB.pack()

            guiParam = gui_Param.GuiParam(nbook.books['Parameter'],
                                          getParam = iface.Param_GetParam,
                                          putParam = iface.Param_PutParam  )
            guiParam.pack()
    
            guiWW = gui_WW.GuiWW(nbook.books['Warmwasser'], 
                                 PuReglerParamSchreiben = iface.WW_PuReglerParamSchreiben,
                                 PuReglerParamLesen     = iface.WW_PuReglerParamLesen      )
            guiWW.pack( padx=PD, pady=PD )
            
            guiWW.t0            = time.time()
            guiWW.xt1.LastPhysX = 0
            guiWW.xt2.LastPhysX = 0
            guiWW.xt1.LastPhysY = 40.0
            guiWW.xt2.LastPhysY = 50.0
    
            guiText = gui_Text.GuiText(nbook.books['Text (Telnet)'], exec_command=iface.HoleAntwort)
            guiText.pack( padx=PD, pady=PD )
            
            connectBtn.config(state=tk.DISABLED)
            servernameEntry.config(state=tk.DISABLED)
    
            # Messwerterfassung starten
            update()
        except:
            pass
    else:
        pass
        
def update():
    global iface, guiFB, guiWW
    try:
        iface.ErmittleMesswerte()
        guiAll.updateLabels(iface.t, iface.pu, iface.mv, iface.di, iface.cnt, iface.av)
        guiFB.updateLabels(iface.t, iface.mv, iface.pu)
        guiWW.plot_MW(iface.t, iface.mv)
    except:
        pass
    if( Aktualisieren_state_tkbl.get() == True ):
        nbook.after_id = nbook.after(5000, update) # rekursiver Aufruf!
            
def beenden():
    global iface
    try:
        iface.beenden()
        iface.close()
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
Aktualisieren_state_tkbl.set(tk.TRUE)
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
